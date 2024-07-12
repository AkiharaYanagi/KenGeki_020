//=================================================================================================
//
//	コリジョン( ぶつかり 衝突 判定 )
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Collision.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Collision::Collision ()
	{
	}

	Collision::~Collision ()
	{
	}


	void Collision::SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p)
	{
		m_pExeChara1p = pExeChara1p;
		m_pExeChara2p = pExeChara2p;
	}


	//相互判定
	void Collision::Do ()
	{
		//両者の接触枠を取得
		P_CharaRect pCharaRect1p = m_pExeChara1p->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_pExeChara2p->GetpCharaRect ();
		PV_RECT pvRect1p = pCharaRect1p->GetpvCRect ();
		PV_RECT pvRect2p = pCharaRect2p->GetpvCRect ();

		//接触判定
		//重なっているとき
		if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
		{
			bool dir1 = m_pExeChara1p->GetDirRight ();
			bool dir2 = m_pExeChara2p->GetDirRight ();
			VEC2 pos1_0 = m_pExeChara1p->GetPos ();
			VEC2 pos2_0 = m_pExeChara2p->GetPos ();

			//重なりをチェックして再取得
			m_pExeChara1p->BackPtX ();	//互いにx方向のみ位置を戻す
			m_pExeChara2p->BackPtX ();

			VEC2 pos1_1 = m_pExeChara1p->GetPos ();
			VEC2 pos2_1 = m_pExeChara2p->GetPos ();

			//さらに重なっているとき
			if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
				//位置をさらに戻して(動作した後の位置)から補正する
				if ( LeaveDir ( dir1, pos1_0.x, pos1_1.x ) )
				{
					m_pExeChara1p->SetPos ( pos1_0 );
				}
				if ( LeaveDir ( dir2, pos2_0.x, pos2_1.x ) )
				{
					m_pExeChara2p->SetPos ( pos2_0 );
				}
			}

			//10回まで再調整
			int i = 0;
			while ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
				m_pExeChara1p->BackMoveX ();	//重なり微調整
				m_pExeChara2p->BackMoveX ();

				m_pExeChara1p->SetCollisionRect ();	//当り枠再設定
				m_pExeChara2p->SetCollisionRect ();

				pvRect1p = pCharaRect1p->GetpvCRect ();
				pvRect2p = pCharaRect2p->GetpvCRect ();

				if ( ++ i > 10 ) { break; }
			}
		}

		//振向
		m_pExeChara1p->LookOther ();
		m_pExeChara2p->LookOther ();

		//距離制限(画面端同士)
		float p1x = m_pExeChara1p->GetPos ().x;
		float p2x = m_pExeChara2p->GetPos ().x;

		//画面左側
		// || P1 << P2			||
		if ( p2x - p1x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_pExeChara1p->BackPtX ();	//互いに位置を戻す
			m_pExeChara2p->BackPtX ();
		}
		//画面右側
		// ||			P2 << P1 ||
		else if ( p1x - p2x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_pExeChara1p->BackPtX ();	//互いに位置を戻す
			m_pExeChara2p->BackPtX ();
		}

	}



	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------
	bool Collision::LeaveDir ( bool dirRight, float pos0, float pos1 )
	{
		//離れる方向のとき
		bool leave = F;
		if ( dirRight )	//右向き左移動
		{
			if ( pos1 < pos0 ) leave = T;
		}
		else//左向き右移動
		{
			if ( pos0 < pos1 ) leave = T;
		}
		return leave;
	}


}	//namespace GAME

