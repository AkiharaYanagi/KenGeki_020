//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaRect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//コンストラクタ
	CharaRect::CharaRect ()
	{
		m_pvCRect = std::make_shared < V_RECT > ();
		m_pvHRect = std::make_shared < V_RECT > ();
		m_pvARect = std::make_shared < V_RECT > ();
		m_pvORect = std::make_shared < V_RECT > ();

		//既定数だけ生成
		m_pvCRect->resize ( NUM_RECT );
		m_pvHRect->resize ( NUM_RECT );
		m_pvARect->resize ( NUM_RECT );
		m_pvORect->resize ( NUM_RECT );
		ResetAllRect ();
#if 0
		for ( UINT i = 0; i < NUM_RECT; ++ i )
		{
			RECT rect = { 0, 0, 0, 0 };
			m_pvCRect->push_back ( rect );
			m_pvARect->push_back ( rect );
			m_pvHRect->push_back ( rect );
			m_pvORect->push_back ( rect );
		}
#endif // 0
	}

	//デストラクタ
	CharaRect::~CharaRect ()
	{
	}


	//全実効枠のリセット
	void CharaRect::ResetAllRect ()
	{
		ZeroVecRect ( m_pvCRect );
		ZeroVecRect ( m_pvHRect );
		ZeroVecRect ( m_pvARect );
		ZeroVecRect ( m_pvORect );
	}

	//枠設定
	void CharaRect::SetpvRect ( PV_RECT pvRectActual, PV_RECT pvRectScript, bool dirRight, VEC2 pos )
	{
		for ( UINT i = 0; i < NUM_RECT; ++ i )
		{
			if ( i < pvRectScript->size () )
			{
				RECT r = pvRectScript->at ( i );
				RECT tempRect {};

				if ( dirRight )	//向き
				{
					tempRect.left	= (LONG)(pos.x + r.left);
					tempRect.top	= (LONG)(pos.y + r.top);
					tempRect.right	= (LONG)(pos.x + r.right);
					tempRect.bottom	= (LONG)(pos.y + r.bottom);
				}
				else 
				{
					tempRect.left	= (LONG)(pos.x - r.right);	//rightと入替
					tempRect.top	= (LONG)(pos.y + r.top);
					tempRect.right	= (LONG)(pos.x - r.left);	//leftと入替
					tempRect.bottom	= (LONG)(pos.y + r.bottom);
				}
				CopyRect ( pvRectActual->at ( i ), tempRect );
			}
			else
			{
				ZeroRect ( pvRectActual->at ( i ) );
			}
		}
	}

	void CharaRect::SetCRect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvCRect, p, dir, pos ); }
	void CharaRect::SetHRect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvHRect, p, dir, pos ); }
	void CharaRect::SetARect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvARect, p, dir, pos ); }
	void CharaRect::SetORect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvORect, p, dir, pos ); }

	
#if 0
	//実効枠から表示枠へ設置
	void CharaRect::SetGrpRect ( PrmRect grpRect [], RECT rect [], float dispGameBaseX )
	{
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			float x = dispGameBaseX + rect[i].left;
			float y = (float)rect[i].top;
			float w = (float)( rect[i].right - rect[i].left );
			float h = (float)( rect[i].bottom - rect[i].top );
			grpRect[i].SetRect ( x, y, w, h );
		}
	}
#endif // 0


}	//namespace GAME

