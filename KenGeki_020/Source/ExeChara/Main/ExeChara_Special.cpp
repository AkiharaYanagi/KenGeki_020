//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
#include "../../FtgMain/Fighting/Fighting.h"
#include "../../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0

	const UINT32 ExeChara::CLR_LOOP [ 8 ] =
	{
		0xff0000ff,
		0xff2020ff,
		0xff4040ff,
		0xff6060ff,
		0xff8080ff,
		0xff6060ff,
		0xff4040ff,
		0xff2020ff,
	};

#endif // 0

	//================================================
	//	特殊アクション指定処理
	//================================================
	void ExeChara::SpecialAction ()
	{
		//-----------------------------------------------------
		//立ち状態でリセット
		if ( IsNameAction ( U"立ち" ) )
		{
			//相手の連続ヒット数のリセット
			m_pOther.lock()->m_btlPrm.SetChainHitNum ( 0 );
		}

		//ダメージでないときもリセット
		if ( ! IsDamaged () )
		{
			m_pOther.lock()->m_btlPrm.SetChainHitNum ( 0 );
		}

		//次が立ちに戻る
		if ( 0 == m_pAction->GetNextName ().compare ( U"立ち" ) )
		{
			//最終スクリプト
			if ( m_pAction->IsEndScript ( m_frame ) )
			{
				//相手の連続ヒット数のリセット
				m_pOther.lock()->m_btlPrm.SetChainHitNum ( 0 );
			}
		}


		//-----------------------------------------------------
		if ( IsNameAction ( U"ダウン" ) )
		{
			if ( m_pOther.lock()->IsNameAction ( U"足払い追撃ヒット" ) )
			{
				m_pOther.lock()->SetAction ( U"立ち" );
			}
		}

		//-----------------------------------------------------
		//空中ダッシュ, 低空ダッシュ
		bool AirDash = IsNameAction ( U"空中ダッシュ" );
		bool LowAirDash = IsNameAction ( U"低空ダッシュ" );
		if ( AirDash || LowAirDash )
		{
			if ( m_frame == 0 )
			{
				m_btlPrm.SetNAirDash ( 1 );
			}
			//回数リセットは "着地" 時
		}

		//@info DBGOUT_WND_F は　ExeChara中で用いると２P側で上書きされる
		if ( IsPlayerID( PLAYER_ID_1 ) )
		{
//			DBGOUT_WND_F( DBGOUT_8, U"AirDash = {}"_fmt( m_btlPrm.GetNAirDash() ) );
		}


		//-----------------------------------------------------
		if ( IsNameAction ( U"剣撃走破" ) )
		{
			//エフェクト発生
			if ( m_pScript->GetFrame () == 5 )
			{
				VEC2 pos = m_btlPrm.GetPos ();
				pos.y += -250;
				m_efSouha->On ( pos );
			}
		}

		if ( IsNameAction ( U"剣撃走破成立" ) )
		{
			//同一アクション内3ヒットで終了
			if ( 4 == m_btlPrm.GetHitNum () )
			{
				SetAction ( U"剣撃走破ヒット" );
			}
		}

		//-----------------------------------------------------
		if ( IsNameAction ( U"超雷電蹴_発生" ) )
		{
			if ( m_pScript->GetFrame () == 1 )
			{
				m_pFtgGrp->SetOverDrive ( T );
			}
		}

		//-----------------------------------------------------
#if 0

		if ( IsNameAction ( U"超必殺A" ) )
		{
			if ( m_pScript->GetFrame () == 1 )
			{
				m_btlPrm.SetPos ( VEC2 ( 0, 0 ) );
			}
		}

#endif // 0

		//-----------------------------------------------------
		if ( IsNameAction ( U"乱舞超必殺技発生" ) )
		{
			if ( m_pScript->GetFrame () == 0 )
			{
//				SND_PLAY_ONESHOT_SE ( SE_Btl_Light );
			}
		}


		//-----------------------------------------------------
		//アクセル増減　 ：　アクション中のアクセル値を利用
		int accel_value = m_pAction->GetAccel ();
		if ( 0 == accel_value ) //スクリプト中で指定なし(==0)
		{
			//カテゴリ一括
			if ( IsAttacking () ) {	m_btlPrm.AddAccel ( 3 ); }	//通常攻撃
			else if ( IsSpecial () ) {	m_btlPrm.AddAccel ( 5 ); }	//必殺技
			else if ( IsOverdrive () ) {	m_btlPrm.AddAccel ( 10 ); }	//超必殺技
			else 
			{
				//０：基本状態は沈静化
				m_btlPrm.DirZeroAccel ( 3 );	//アクセル 沈静化
			}
		}
		else if ( 0 < accel_value ) //プラス時
		{
			m_btlPrm.AddAccel ( accel_value );
		}
		else //マイナス時
		{
			//０：基本状態は沈静化
			//m_btlPrm.DirZeroAccel ( 3 );	//アクセル 沈静化

			//マイナス分
			m_btlPrm.AddAccel ( accel_value - 3 );
		}



#if 0

		//-----------------------------------------------------
		//足払い追撃終了
//		if ( IsNameAction ( _T ( "足払い追撃ヒット" ) ) )
		if ( IsNameAction ( _T ( "ホーミング" ) ) )
//		if ( IsNameAction ( _T ( "テスト" ) ) )
		{
			if ( m_frame == 0 )
			{
				G_FTG()->SetWallMove ( T );
			}

//			if ( m_pAction->IsOverScript ( m_frame ) )
			if ( m_pAction->IsEndScript ( m_pScript->GetFrame() ) )
			{
//				G_FTG()->SetWallMove ( F );
			}
		}
		if ( IsNameAction ( _T ( "位置リセット着地" ) ) )
		{
			if ( m_frame == 0 )
			{
				G_FTG()->SetWallMove ( F );
			}
		}



		if ( IsNameAction ( _T ( "空中ダッシュ小攻撃" ) ) 
			||  IsNameAction ( _T ( "空中ダッシュ中攻撃" ) ) 
			||  IsNameAction ( _T ( "空中ダッシュ大攻撃" ) ) 
			)
		{
			//攻撃成立時
			if ( m_btlPrm.GetHitEst () )
			{
				m_btlPrm.SetHitDrop ( 2.5 );
			}
		}

#if 0
		//-----------------------------------------------------
		//バランスアウト
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			//			SetAction ( _T ( "Dotty" ) );
			SetAction ( _T ( "立ち" ) );
		}
#endif // 0

		//=====================================================
		// キャラ別分岐
		
		//-----------------------------------------------------
		//壁まで吹き飛び
		if ( IsNameAction ( _T ( "小攻撃" ) ) )
		{
			if ( m_frame == 0 )
			{
				int i = 0;
			}
		}

		//-----------------------------------------------------
		//壁まで吹き飛び
		if ( IsNameAction ( _T ( "壁まで吹き飛び" ) ) )
		{
			if ( m_frame == 0 )
			{
			}

			//カラー遷移
			static UINT32 index = 0;
			if ( index >= CLR_LOOP_NUM )
			{
				index = 0;
			}
			m_btlPrm.SetColor ( CLR_LOOP [ index ++ ] );
		}

		//-----------------------------------------------------
		//壁割り発生
		if ( IsNameAction ( _T ( "壁張り付き" ) ) )
		{
			if ( m_frame == 0 )
			{
#if 0
				if ( m_btlPrm.GetDirRight () )
				{
					mwp_fighting.lock()->WallBreak_L ();
				}
				else
				{
					mwp_fighting.lock()->WallBreak_R ();
				}

				//相手を強制的に"壁割り後の走り"に移行する
				
				G_FTG()->SetNewWall ( T );
#endif // 0
				m_btlPrm.SetColor ( 0xffffffff );
			}
		}

		//-----------------------------------------------------
		//必殺技A
		if ( IsNameAction ( _T ( "必殺技A" ) ) )
		{
			//相手色変更
			m_pOther.lock ()->m_btlPrm.SetColor ( 0xff0000ff );
		}

		//-----------------------------------------------------
		//超必殺背景演出
		if ( IsNameAction ( _T ( "超必Bヒット後" ) ) )
		{
			if ( m_frame == 0 )
			{
				//ライフ判定
				if ( m_pOther.lock()->GetLife () < 3000 )
				{
					//倒しきり時分岐
					SetAction ( _T ( "超必B_特殊勝利" ) );
				}

				//背景白転　キャラ影演出
				m_dispChara->TurnShadow ( T );
				m_btlPrm.SetWhiteOut ( T );
				m_pOther.lock()->m_dispChara->TurnShadow ( T );
			}
		}

		if (	IsNameAction ( _T ( "超必Bヒット終了" ) ) 
			||	IsNameAction ( _T ( "超必B_特殊勝利終了" ) ) 
		)
		{
			if ( m_frame == 0 )
			{
				//演出解除
				m_dispChara->TurnShadow ( F );
				m_pOther.lock()->m_dispChara->TurnShadow ( F );
			}
		}
#endif // 0

	}




}	//namespace GAME

