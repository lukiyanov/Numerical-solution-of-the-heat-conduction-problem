// MatrixView.cpp: файл реализации
//

#include "stdafx.h"
#include "RK_frontend.h"
#include "MatrixView.h"
#include "MainFrm.h"
#include "TaskResult.h"
#include "lang\MathExpression.h"

// CMatrixView

IMPLEMENT_DYNAMIC(CMatrixView, CWnd)

CMatrixView::CMatrixView()
	:m_bachgroundBrush(RGB(255, 255, 255)),
	m_penGraph(PS_NULL, 0, RGB(128, 255, 128)),
	m_penGrid(PS_DOT, 1, RGB(128, 128, 255)),
	m_pBodyExpression(0), m_aIsBodyPoint(0)
{
	// Создаём стандартный шрифт шиндовс.
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	LOGFONT lfDlgFont = ncm.lfMessageFont;
	m_fontStd.CreateFontIndirect(&lfDlgFont);

	for (int i = 0; i < 256; i++)
	{
		m_brushes[i] = new CBrush(RGB(i, 80, 128));
		m_pens[i] = new CPen(PS_SOLID, 1, RGB(i, 80, 128));
	}
}

CMatrixView::~CMatrixView()
{
	for (int i = 0; i < 256; i++)
	{
		delete m_brushes[i];
		delete m_pens[i];
	}

	delete m_pBodyExpression;
}

BOOL CMatrixView::Create(CWnd* pParentWnd)
{
	BOOL bResult = CWnd::Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), pParentWnd, AFX_IDW_PANE_FIRST, NULL);
	return bResult;
}

BEGIN_MESSAGE_MAP(CMatrixView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений CMatrixView

bool CMatrixView::SetResult(TaskResult* pResult)
{
	if (!pResult)
		return false;

	if (pResult->m_resultStatus != lang::TaskResult::RESULT_SUCCESS)
		return false;

	if (pResult->m_task.taskType == lang::TaskType::BUILD_FULL_BODY_FOR_TIME)
	{
		delete m_pBodyExpression;
		m_pBodyExpression = new lang::MathExpression(pResult->m_task.strBodyExpression);
		if (m_pBodyExpression->GetVariableCount() == 2)
		{
			std::vector<std::string> names;
			m_pBodyExpression->GetVariableNames(names);

			m_vctPoints = pResult->BUILD_FULL_BODY_FOR_TIME.vctPointsXY;
			m_strVarXName = names[0].c_str();
			m_strVarYName = names[1].c_str();


			m_minX = pResult->m_task.dblVar0From;
			m_maxX = pResult->m_task.dblVar0To;
			m_minY = pResult->m_task.dblVar1From;
			m_maxY = pResult->m_task.dblVar1To;

			m_intervalsX = pResult->m_task.nVar0IntervalCount;
			m_intervalsY = pResult->m_task.nVar1IntervalCount;

			m_minT = m_vctPoints[0].temperature;
			m_maxT = m_vctPoints[0].temperature;

			for (size_t i = 1, size = m_vctPoints.size(); i < size; i++)
			{
				if (m_vctPoints[i].temperature < m_minT)
					m_minT = m_vctPoints[i].temperature;

				if (m_maxT < m_vctPoints[i].temperature)
					m_maxT = m_vctPoints[i].temperature;
			}

			m_width = m_maxX - m_minX;
			m_height = m_maxY - m_minY;


			// Вычисляем, какие точки принадлежат телу.
			const size_t size = m_vctPoints.size();

			delete m_aIsBodyPoint;
			m_aIsBodyPoint = new bool[size];

			double args[2];
			for (size_t i = 0; i < size; i++)
			{
				args[0] = m_vctPoints[i].x;
				args[1] = m_vctPoints[i].y;
				m_aIsBodyPoint[i] = m_pBodyExpression->Calculate(args).boolValue;
			}

			return true;
		}
	}

	return false;
}

void CMatrixView::OnPaint()
{
	// Можно было бы всё закэшировать чтобы повысить скорость отрисовки, но мне лень.

	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, &m_bachgroundBrush);

	const int graphBorderWidth = static_cast<int>(0.8 * rect.Width());
	const int graphBorderHeight = static_cast<int>(0.9 * rect.Height());
	const int graphBorderX = static_cast<int>(0.05 * rect.Width());
	const int graphBorderY = static_cast<int>(0.05 * rect.Height());

	dc.Rectangle(graphBorderX, graphBorderY, graphBorderX + graphBorderWidth, graphBorderY + graphBorderHeight);

	const int graphWidth = static_cast<int>(0.7 * rect.Width());
	const int graphHeight = static_cast<int>(0.8 * rect.Height());
	const int graphX = static_cast<int>(0.1 * rect.Width());
	const int graphY = static_cast<int>(0.1 * rect.Height());

	dc.SelectObject(&m_fontStd);
	dc.SelectObject(m_penGrid);

	const int window_height = rect.bottom;
	// Наносим деления по X aka времени.
	rect.top = graphBorderY + graphBorderHeight + 2;
	rect.bottom = rect.top + 100;

	for (int i = 0; i <= 11; i++)
	{
		const int left = static_cast<int>(graphX + graphWidth * 0.1 * i);
		rect.left = left - 2;
		rect.right = rect.left + 100;

		if (i == 11)
			dc.DrawText(m_strVarXName, &rect, 0);
		else
		{
			dc.MoveTo(left, graphBorderY + graphBorderHeight - 5);
			dc.LineTo(left, graphBorderY + 5);

			dc.DrawText(CString(lang::ToString(m_minX + m_width * 0.1 * i).c_str()), &rect, 0);
		}
	}

	// Наносим деления по Y aka температуре.
	rect.left = graphBorderX - 30;
	if (rect.left < 0) rect.left = 0;
	rect.right = graphBorderX;

	for (int i = 0; i <= 11; i++)
	{
		const int top = graphY + static_cast<int>(graphHeight * (1 - 0.1 * i));
		rect.top = top - 5;
		rect.right = rect.left + 100;

		if (i == 11)
			dc.DrawText(m_strVarYName, &rect, 0);
		else
		{
			dc.MoveTo(graphBorderX + 5, top);
			dc.LineTo(graphBorderX + graphBorderWidth - 5, top);

			dc.DrawText(CString(lang::ToString(m_minY + m_height * 0.1 * i).c_str()), &rect, 0);
		}
	}

	// Срём прямоугольниками.
	for (size_t i = 0, size = m_vctPoints.size(); i < size; i++)
	{
		const int pointX = static_cast<int>(graphX + ((m_width  > 0) ? graphWidth                * (m_vctPoints[i].x - m_minX) / m_width : 0));
		const int pointY = static_cast<int>(graphY + ((m_height > 0) ? graphHeight - graphHeight * (m_vctPoints[i].y - m_minY) / m_height : 0));

		// Ширина и высота прямоугольника, разделённые на два.
		const int rectWidth2 = graphWidth / (m_intervalsX * 2);
		const int rectHeight2 = graphHeight / (m_intervalsY * 2);

		// Выбираем цвет прямоугольника, в зависимости от температуры.
		CBrush* pBrush = GetBrush(m_vctPoints[i].temperature, m_minT, m_maxT);
		dc.SelectObject(pBrush);

		if (m_aIsBodyPoint[i])
		{
			dc.SelectObject(m_penGraph);
			dc.Rectangle(pointX - rectWidth2, pointY - rectHeight2, pointX + rectWidth2, pointY + rectHeight2);
		}
		else
		{
			// Если точка не принадлежит телу -- штрихуем прямоугольник температуры цветом фона (белым).
			LOGBRUSH br;
			pBrush->GetLogBrush(&br);

			CPen penEnvironment(PS_SOLID, 1, br.lbColor);

			dc.SelectObject(&penEnvironment);

			dc.MoveTo(pointX - rectWidth2, pointY - rectHeight2);
			dc.LineTo(pointX + rectWidth2, pointY + rectHeight2);

			dc.MoveTo(pointX - rectWidth2, pointY);
			dc.LineTo(pointX, pointY + rectHeight2);

			dc.MoveTo(pointX + rectWidth2, pointY);
			dc.LineTo(pointX, pointY - rectHeight2);

			dc.MoveTo(pointX + rectWidth2, pointY - rectHeight2);
			dc.LineTo(pointX - rectWidth2, pointY + rectHeight2);

			dc.MoveTo(pointX + rectWidth2, pointY);
			dc.LineTo(pointX, pointY + rectHeight2);

			dc.MoveTo(pointX - rectWidth2, pointY);
			dc.LineTo(pointX, pointY - rectHeight2);
		}
	}

	// Рисуем легенду цвета сбоку.
	const int x = graphBorderX + graphBorderWidth + 5;
	const int w = x + static_cast<int>(0.1 * rect.Width());
	for (int i = 0; i < 256; i++)
	{
		const int y = graphBorderY + i;

		dc.SelectObject(m_pens[255 - i]);
		dc.MoveTo(x, y);
		dc.LineTo(w, y);
	}

	// Наносим деления на легенду.
	rect.left = graphBorderX + graphBorderWidth + 10 + static_cast<int>(0.1 * rect.Width());
	rect.right = x + 100;

	for (int i = 0; i < 5; i++)
	{
		rect.top = graphBorderY + static_cast<int>(246 * (0.25 * i)); // 246 = 256-10, чтобы шрифт не слишком далеко вылез за края шкалы
		rect.bottom = rect.top + 100;

		CString note = CString("T=") + lang::ToString(m_maxT - (m_maxT - m_minT) * 0.25 * i).c_str();
		dc.DrawText(note, &rect, 0);
	}
}

CBrush* CMatrixView::GetBrush(const double temperature, const double m_minT, const double m_maxT)
{
	const double coeff = (m_maxT != m_minT) ? ((temperature - m_minT) / (m_maxT - m_minT)) : 0;

	return m_brushes[static_cast<int>(coeff * 255)];
}
