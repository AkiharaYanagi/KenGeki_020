//=================================================================================================
//
// ExeEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//@Later	いずれEffectにEfGnrtを統合
	//------------------------------------------

	ExeEffect::ExeEffect ( P_Effect pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight )
	 :	  m_active ( true ), m_end ( false ), m_frame ( 0 )
		, m_ptEffect ( VEC2 ( 0, 0 ) ), m_dirRight ( dirRight )
		, m_vel ( VEC2 ( 0, 0 ) ), m_acc ( VEC2 ( 0, 0 ) )
		, m_pEffect ( pEffect ), m_pScript ( nullptr ) 
		, m_bDispRect ( true )
		, m_offset ( false ), m_hit ( false )
	{
		SetpEfGnrt ( pEfGnrt );
		m_pScript = m_pEffect->GetpScript ( 0 );

		m_pChara = pChara;
		m_vpBranch = pChara->GetvpBranch ();
		m_vpRoute = pChara->GetvpRoute ();

		//初期位置 (キャラ位置+エフェクト発生位置)
		m_ptEffect = ptChara + Dir ( m_ptGnrt );

		//枠
		m_charaRect = std::make_shared < CharaRect > ();

		//表示
		m_dispEffect = std::make_shared < DispEffect > ( pChara->GetpapEfTexture (), pEfGnrt->GetZ () );
		AddpTask ( m_dispEffect );
	}

	ExeEffect::~ExeEffect ()
	{
		m_dispEffect.reset ();
	}

	void ExeEffect::SetpEfGnrt ( P_EfGnrt p )
	{
		m_ptGnrt = p->GetPos ();
		m_gnrt = p->GetGnrt ();
		m_loop = p->GetLoop ();
		m_sync = p->GetSync ();
	}

	void ExeEffect::Init ()
	{
		m_active = F;
		m_end = F;
		m_frame = 0;
		m_ptEffect = VEC2 ( 0, 0 );
		m_vel = VEC2 ( 0, 0 );
		m_acc = VEC2 ( 0, 0 );
		m_dispEffect->SetValid ( F );
		m_offset = F;
		m_hit = F;
		TASK_VEC::Init ();
	}


	void ExeEffect::Disp ()
	{
		//表示更新
		m_dispEffect->Update ( m_pScript, m_ptEffect, m_dirRight );

		//枠表示
		if ( m_bDispRect )
		{
			m_dispEffect->OnRect ();
			m_dispEffect->SetpCharaRect ( m_charaRect );
		}
		else
		{
			m_dispEffect->OffRect ();
		}
	}


	void ExeEffect::PreScriptMove ()
	{
		//スクリプトを取得
		m_pScript = m_pEffect->GetpScript ( m_frame );

		//エフェクト終了条件
		//画面外のとき終了
		if ( m_ptEffect.x < 0 - 100 || GAME_WIDTH + 100 < m_ptEffect.x )
		{
			m_end = true;
		}

		//エフェクト移項用
		UINT sqcID = 0;

		//現在エフェクトが最終フレームならば
		if ( m_pEffect->IsEndScript ( m_frame ) )
		{
			bool bBranch = false;

			//スクリプト分岐条件から

			//ルートのチェック
			V_UINT vec_RouteID = m_pScript->GetcvRouteID ();
			for ( UINT indexRoute : vec_RouteID )
			{
				//ブランチのチェック
				V_UINT vBranchID = m_vpRoute[indexRoute]->GetcvIDBranch ();
				for ( UINT indexBranch : vBranchID )
				{
					//終了時以外は飛ばす
					if ( BRC_END == m_vpBranch[indexBranch]->GetCondition () )
					{
						//次シークエンスID
						sqcID = m_vpBranch[indexBranch]->GetIndexSequence ();
						bBranch = true;
					}
				}
			}
			
			if ( bBranch )
			{
				//@todo シークエンス(エフェクト)内でエフェクトの移項
				m_pEffect = m_pChara->GetpEffect ( sqcID );
				m_frame = 0;
			}
			else
			{
				if ( m_loop )
				{
					m_frame = 0;	//ループ
				}
				else
				{
					m_end = true;	//終了
				}
			}
		}
		else
		{
			++ m_frame;	//続行
		}


		//特殊指定
		if ( m_pEffect->IsName ( U"Laser_m" ) )
		{
			static float w = 1.f;
			m_dispEffect->SetW ( w += 1.f );
			m_pScript->m_prmStaging.Rotate_center = VEC2 ( 0, 128 );
			if ( m_pEffect->IsEndScript ( m_frame ) )
			{
				m_dispEffect->SetW ( w = 0 );
			}
		}
	}

	void ExeEffect::PostScriptMove ( BtlParam & btlprm )
	{
		//ゲーム位置計算 (表示位置はDispで計算する)
		//@info Exeでゲーム位置を計算し、Dispで画面位置補正を加算する

		VEC2 ptChara = btlprm.GetPos ();
		bool dirRight = btlprm.GetDirRight ();

		//判定後ヒット時or相殺時
		if ( m_hit || m_offset )
		{
			m_end = true;
			return;
		}

		//エフェクト基準位置
		if ( m_sync )		//キャラ同期フラグで分岐
		{
			//エフェクト位置 = キャラ位置 + 発生位置
			m_ptEffect = ptChara + Dir ( m_ptGnrt );

			//向き
			m_dirRight = dirRight;
		}

		//速度計算
		m_ptEffect += Dir ( m_pScript->m_prmBattle.Vel );

		//枠設定
		m_charaRect->SetARect ( m_pScript->GetpvARect (), m_dirRight, m_ptEffect );

		//表示
		Disp ();
	}

	void ExeEffect::SynchroScript ( VEC2 ptChara )
	{
		m_ptEffect = ptChara;
	}


}	//namespace GAME

