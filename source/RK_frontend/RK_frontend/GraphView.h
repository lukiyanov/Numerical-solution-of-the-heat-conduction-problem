#pragma once
#include "TaskResult.h"
#include <vector>

class CGraphView : public CWnd
{
	DECLARE_DYNAMIC(CGraphView)
	
	CBrush m_bachgroundBrush;
	CPen m_penGraph;
	CPen m_penGrid;
	CFont m_fontStd;

	double m_minT, m_maxT, m_minTime, m_maxTime;
	double m_width, m_height;

	CString m_strBottomVarName;

public:
	CGraphView();
	virtual ~CGraphView();
	BOOL Create(CWnd* pParentWnd);

	bool SetResult(TaskResult* pResult);

protected:
	void SetPoints(const std::vector<TaskResult::PointT>& vctPointsT);
	// Используется только первая переменная, пригодно для одномерных задач.
	void SetPoints(const std::vector<TaskResult::PointXY>& vctPointsXY, const CString& strBottomVarName);
	void SetBorders();

protected:
	std::vector<TaskResult::PointT> m_vctPoints;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


