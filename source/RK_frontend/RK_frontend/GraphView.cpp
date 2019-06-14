// GraphView.cpp: файл реализации
//

#include "stdafx.h"
#include "RK_frontend.h"
#include "GraphView.h"
#include "MainFrm.h"
#include "lang\Transformation.h"
#include "lang\MathExpression.h"

// CGraphView

IMPLEMENT_DYNAMIC(CGraphView, CWnd)

CGraphView::CGraphView()
	:m_bachgroundBrush(RGB(255, 255, 255)),
	m_penGraph(PS_SOLID, 2, RGB(255, 50, 50)),
	m_penGrid(PS_DOT, 1, RGB(128, 128, 255))
{
	// Создаём стандартный шрифт шиндовс.
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	LOGFONT lfDlgFont = ncm.lfMessageFont;
	m_fontStd.CreateFontIndirect(&lfDlgFont);
}

CGraphView::~CGraphView()
{
}

BOOL CGraphView::Create(CWnd* pParentWnd)
{
	BOOL bResult = CWnd::Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), pParentWnd, AFX_IDW_PANE_FIRST, NULL);
	return bResult;
}


BEGIN_MESSAGE_MAP(CGraphView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений CGraphView

void CGraphView::SetPoints(const std::vector<TaskResult::PointT>& vctPointsT)
{
	m_vctPoints = vctPointsT;
	m_strBottomVarName = "t";
	SetBorders();
}

void CGraphView::SetPoints(const std::vector<TaskResult::PointXY>& vctPointsXY, const CString& strBottomVarName)
{
	const size_t size = vctPointsXY.size();
	m_vctPoints.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		m_vctPoints[i].temperature = vctPointsXY[i].temperature;
		m_vctPoints[i].time = vctPointsXY[i].x;
	}

	m_strBottomVarName = strBottomVarName;
	SetBorders();
}

void CGraphView::SetBorders()
{
	size_t size = m_vctPoints.size();
	if (!size)
		return;

	m_minTime = m_vctPoints[0].time;
	m_maxTime = m_vctPoints[size - 1].time;

	m_minT = m_vctPoints[0].temperature;
	m_maxT = m_vctPoints[0].temperature;

	for (size_t i = 1; i < size; i++)
	{
		if (m_vctPoints[i].temperature < m_minT)
			m_minT = m_vctPoints[i].temperature;

		if (m_maxT < m_vctPoints[i].temperature)
			m_maxT = m_vctPoints[i].temperature;
	}

	m_width  = m_maxTime - m_minTime;
	m_height = m_maxT - m_minT;
}

bool CGraphView::SetResult(TaskResult* pResult)
{
	if (!pResult)
		return false;

	if (pResult->m_resultStatus != lang::TaskResult::RESULT_SUCCESS)
		return false;

	if (pResult->m_task.taskType == lang::TaskType::BUILD_TEMPERATURE_CHANGES_FOR_POINT)
	{
		SetPoints(pResult->BUILD_TEMPERATURE_CHANGES_FOR_POINT.vctPointsT);
		return true;
	}

	if (pResult->m_task.taskType == lang::TaskType::BUILD_FULL_BODY_FOR_TIME)
	{
		lang::MathExpression body(pResult->m_task.strBodyExpression);
		if (body.GetVariableCount() == 1)
		{
			std::vector<std::string> names;
			body.GetVariableNames(names);
			SetPoints(pResult->BUILD_FULL_BODY_FOR_TIME.vctPointsXY, CString(names[0].c_str()));
			return true;
		}
	}

	return false;
}

void CGraphView::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, &m_bachgroundBrush);

	const int graphBorderWidth  = static_cast<int>(0.9 * rect.Width());
	const int graphBorderHeight = static_cast<int>(0.9 * rect.Height());
	const int graphBorderX      = static_cast<int>(0.05 * rect.Width());
	const int graphBorderY      = static_cast<int>(0.05 * rect.Height());

	dc.Rectangle(graphBorderX, graphBorderY, graphBorderX + graphBorderWidth, graphBorderY + graphBorderHeight);

	const int graphWidth  = static_cast<int>(0.8 * rect.Width());
	const int graphHeight = static_cast<int>(0.8 * rect.Height());
	const int graphX      = static_cast<int>(0.1 * rect.Width());
	const int graphY      = static_cast<int>(0.1 * rect.Height());


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
			dc.DrawText(m_strBottomVarName, &rect, 0);
		else
		{
			dc.MoveTo(left, graphBorderY + graphBorderHeight - 5);
			dc.LineTo(left, graphBorderY + 5);

			dc.DrawText(CString(lang::ToString(m_minTime + m_width * 0.1 * i).c_str()), &rect, 0);
		}
	}

	// Наносим деления по Y aka температуре.
	rect.left  = graphBorderX - 30;
	if (rect.left < 0) rect.left = 0;
	rect.right = graphBorderX;

	for (int i = 0; i <= 11; i++)
	{
		const int top = graphY + static_cast<int>(graphHeight * (1 - 0.1 * i));
		rect.top   = top - 5;
		rect.right = rect.left + 100;

		if (i == 11)
			dc.DrawText(L"T", &rect, 0);
		else
		{
			dc.MoveTo(graphBorderX + 5, top);
			dc.LineTo(graphBorderX + graphBorderWidth - 5, top);

			dc.DrawText(CString(lang::ToString(m_minT + m_height * 0.1 * i).c_str()), &rect, 0);
		}
	}

	// Выводим график.
	dc.SelectObject(m_penGraph);
	for (size_t i = 1, size = m_vctPoints.size(); i < size; i++)
	{
		const int fromX = static_cast<int>(graphX + ((m_width  > 0) ? graphWidth                * (m_vctPoints[i - 1].time - m_minTime) / m_width : 0));
		const int fromY = static_cast<int>(graphY + ((m_height > 0) ? graphHeight - graphHeight * (m_vctPoints[i - 1].temperature - m_minT) / m_height : 0));
		const int toX   = static_cast<int>(graphX + ((m_width  > 0) ? graphWidth                * (m_vctPoints[i].time - m_minTime) / m_width : 0));
		const int toY   = static_cast<int>(graphY + ((m_height > 0) ? graphHeight - graphHeight * (m_vctPoints[i].temperature - m_minT) / m_height : 0));

		dc.MoveTo(fromX, fromY);
		dc.LineTo(toX, toY);
	}
}
