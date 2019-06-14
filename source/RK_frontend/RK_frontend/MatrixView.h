#pragma once
#include "TaskResult.h"

namespace lang { class MathExpression; }

class CMatrixView : public CWnd
{
	DECLARE_DYNAMIC(CMatrixView)

	CBrush m_bachgroundBrush;
	CPen m_penGraph, m_penGrid;
	CFont m_fontStd;

	CBrush* m_brushes[256];
	CPen* m_pens[256];

	CString m_strVarXName;
	CString m_strVarYName;

	double m_minT, m_maxT, m_minX, m_maxX, m_minY, m_maxY;
	double m_width, m_height;
	int m_intervalsX, m_intervalsY;

	std::vector<TaskResult::PointXY> m_vctPoints;

	lang::MathExpression* m_pBodyExpression;
	bool* m_aIsBodyPoint;

public:
	CMatrixView();
	virtual ~CMatrixView();
	BOOL Create(CWnd* pParentWnd);

	bool SetResult(TaskResult* pResult);

protected:
	CBrush* GetBrush(const double temperature, const double m_minT, const double m_maxT);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};


