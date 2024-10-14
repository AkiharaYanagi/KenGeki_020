//=================================================================================================
//
// DispFrontEnd ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispFrontEnd.h"
#include "DispChara_Const.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	VEC2 DispFrontEnd::POS_PL_CP_1P ( 5, LIFE_GAUGE_Y - 18 );
	VEC2 DispFrontEnd::POS_PL_CP_2P ( 1280 - 64 - 5, LIFE_GAUGE_Y - 18 );


	DispFrontEnd::DispFrontEnd ()
	{
		//ゲージ類

		//ライフゲージ
		m_gaugeLife = std::make_shared < DispGauge > ();
		m_gaugeLife->SetPosition ( LIFE_GAUGE_X, LIFE_GAUGE_Y, LIFE_GAUGE_W, LIFE_GAUGE_H );
		m_gaugeLife->SetPadding ( LIFE_GAUGE_P );
		m_gaugeLife->SetZ ( Z_SHADOW );
		m_gaugeLife->SetTextureName_Frame ( U"gauge_life_frame_2p.png" );
		m_gaugeLife->SetTextureName_Value ( U"gauge_life_value_2p.png" );
		m_gaugeLife->SetTextureName_Decrease ( U"gauge_life_decrease_2p.png" );
		m_gaugeLife->SetTextureName_White ( U"gauge_life_white_2p.png" );
//	m_gaugeLife->SetColor_Decrease ( LIFE_GAUGE_DECREASE_CLR );
		m_gaugeLife->OnWhite ();
		AddpTask ( m_gaugeLife );

		//バランスゲージ
		m_gaugeBalance = std::make_shared < DispGauge > ();
		m_gaugeBalance->SetPosition ( BALANCE_GAUGE_X, BALANCE_GAUGE_Y, BALANCE_GAUGE_W, BALANCE_GAUGE_H );
		m_gaugeBalance->SetPadding ( BALANCE_GAUGE_P );
		m_gaugeBalance->SetZ ( Z_SHADOW );
		m_gaugeBalance->SetTextureName_Frame ( U"gauge_balance_frame.png" );
		m_gaugeBalance->SetTextureName_Value ( U"gauge_balance_value.png" );
		m_gaugeBalance->OffDecrease ();
		m_gaugeBalance->OffWhite ();
		AddpTask ( m_gaugeBalance );

		//マナゲージ
		m_gaugeMana = std::make_shared < DispGauge > ();
		m_gaugeMana->SetPosition ( MANA_GAUGE_X, MANA_GAUGE_Y, MANA_GAUGE_W, MANA_GAUGE_H );
		m_gaugeMana->SetPadding ( MANA_GAUGE_P );
		m_gaugeMana->SetZ ( Z_SYS );
		m_gaugeMana->SetTextureName_Frame ( U"gauge_mana_frame.png" );
		m_gaugeMana->SetTextureName_Value ( U"gauge_mana_value.png" );
		m_gaugeMana->SetPadding ( MANA_GAUGE_P );
		m_gaugeMana->OffDecrease ();
		m_gaugeMana->OffWhite ();
		AddpTask ( m_gaugeMana );

		//アクセルゲージ
		m_gaugeAccel = std::make_shared < DispAccel > ();
		AddpTask ( m_gaugeAccel );


		//-----------------------------------------------------
		//プレイヤー表示
		//-----------------------------------------------------
#if 0
		m_grp_Cst_Player1P2P = MakepGrpPlyr ( _T ( "Player_1P.png" ) );
		m_grp_Cst_Player1P2P->AddTexture ( _T ( "Player_2P.png" ) );

		m_grp_Cst_InputPlayerCOM = MakepGrpPlyr ( _T ( "INPUT_PLAYER.png" ) );
		m_grp_Cst_InputPlayerCOM->AddTexture ( _T ( "INPUT_CPU.png" ) );

		m_grp_CH_Player1P2P = MakepGrpPlyr ( _T ( "Player_1P.png" ) );
		m_grp_CH_Player1P2P->AddTexture ( _T ( "Player_2P.png" ) );

		m_grp_CH_InputCOMPLayer = MakepGrpPlyr ( _T ( "INPUT_PLAYER.png" ) );
		m_grp_CH_InputCOMPLayer->AddTexture ( _T ( "INPUT_CPU.png" ) );

//		m_grp_Cst_Player1P2P->SetValid ( F );
//		m_grp_Cst_InputPlayerCOM->SetValid ( F );
		m_grp_CH_Player1P2P->SetValid ( F );
		m_grp_CH_InputCOMPLayer->SetValid ( F );

#endif // 0

#if 0
		//ヒットストップ時間表示
		m_gaugeHitStop.SetAllColor ( _CLR ( 0xffa0a0ff ) );
		m_pGrpAry->InsertTask ( & m_gaugeHitStop );

		//のけぞり時間表示
		m_gaugeLurch.SetAllColor ( _CLR ( 0xffa0ffa0 ) );
		m_pGrpAry->InsertTask ( & m_gaugeLurch );
#endif	//0

		//ヒット数
		m_grpHitNum = std::make_shared < GameGraphic > ();
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\0.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\1.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\2.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\3.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\4.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\5.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\6.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\7.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\8.png" );
		m_grpHitNum->AddTexture_FromArchive ( U"hit\\9.png" );
		m_grpHitNum->SetZ ( Z_EFB + 0.01f );
		m_grpHitNum->SetValid ( F );
		AddpTask ( m_grpHitNum );
		GRPLST_INSERT ( m_grpHitNum );

		//ヒット数２桁目
		m_grpHitNum->AddObject ();

		m_grpStrHit = std::make_shared < GameGraphic > ();
		m_grpStrHit->AddTexture_FromArchive ( U"Hit.png" );
		m_grpStrHit->SetZ ( Z_EFB + 0.01f );
		m_grpStrHit->SetValid ( F );
		AddpTask ( m_grpStrHit );
		GRPLST_INSERT ( m_grpStrHit );


		//------------------------------------------------------
		//アクション名
		m_strAction = std::make_shared < GrpStr > ();
		m_strAction->SetStr ( U"Action" );
		m_strAction->SetZ ( Z_MENU );
		m_strAction->SetSize ( G_Font::SIZE_40 );
		m_strAction->SetColorF ( s3d::ColorF { 0.8f, 0.8f, 1.f, 1.f } );
		GRPLST_INSERT ( m_strAction );
		AddpTask ( m_strAction );

		//ステート名
		m_strState = std::make_shared < GrpStr > ();
		m_strState->SetStr ( U"State" );
		m_strState->SetZ ( Z_MENU );
		m_strState->SetSize ( G_Font::SIZE_40 );
		m_strState->SetColorF ( s3d::ColorF { 0.0f, 0.0f, 0.5f, 1.f } );
		GRPLST_INSERT ( m_strState );
		AddpTask ( m_strState );
	}

	//オブジェクト生成用
	P_Grp DispFrontEnd::MakepGrpPlyr ( s3d::String str )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->SetValid ( T );
		p->AddTexture ( str );
		p->SetZ ( Z_SYS + 0.06f );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	DispFrontEnd::~DispFrontEnd ()
	{
	}

	void DispFrontEnd::Load ()
	{
		m_strAction->SetSize ( G_Font::SIZE_40 );
		m_strState->SetSize ( G_Font::SIZE_40 );
		TASK_VEC::Load ();
	}


	void DispFrontEnd::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		m_gaugeLife->LoadPlayer ( playerID );
		m_gaugeBalance->LoadPlayer ( playerID );
		m_gaugeMana->LoadPlayer ( playerID );
		m_gaugeAccel->LoadPlayer ( playerID );
#if 0


		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_grp_Cst_Player1P2P->SetPos ( POS_PL_CP_1P );
			m_grp_Cst_Player1P2P->SetIndexTexture ( SIDE_1P );

			m_grp_Cst_InputPlayerCOM->SetPos ( POS_PL_CP_1P + VEC2 ( 0, 33 ) );
			m_grp_CH_Player1P2P->SetIndexTexture ( SIDE_1P );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_grp_Cst_Player1P2P->SetPos ( POS_PL_CP_2P );
			m_grp_Cst_Player1P2P->SetIndexTexture ( SIDE_2P );

			m_grp_Cst_InputPlayerCOM->SetPos ( POS_PL_CP_2P + VEC2 ( 0, 33 ) );
			m_grp_CH_Player1P2P->SetIndexTexture ( SIDE_2P );
		}
#endif // 0

#if 0
		//ヒットストップ時間表示
		m_gaugeHitStop.SetRect ( 0, 0, 0, 0 );

		//のけぞり時間表示
		m_gaugeLurch.SetRect ( 0, 0, 0, 0 );
#endif // 0


		//ヒット数
		P_Ob pOb = m_grpHitNum->GetpObject ( 1 );
		if ( PLAYER_ID_1 == playerID )
		{
			m_grpHitNum->SetPos ( VEC2 ( 100, 200 ) );
			m_grpStrHit->SetPos ( VEC2 ( 100 + 128, 200 ) );
			
			pOb->SetPos ( VEC2 ( 0, 200 ) );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_grpHitNum->SetPos ( VEC2 ( 1280 - 384 -100, 200 ) );
			m_grpStrHit->SetPos ( VEC2 ( 1280 - 256 -100, 200 ) );

			pOb->SetPos ( VEC2 (  1280 - 384 - 0, 200 ) );
		}


		//アクション名　位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_strAction->SetPos ( VEC2 ( 140, 120 ) );
			m_strState->SetPos ( VEC2 ( 140, 160 ) );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_strAction->SetPos ( VEC2 ( 640 + 390, 120 ) );
			m_strState->SetPos ( VEC2 ( 640 + 390, 160 ) );
		}

	}


	//------------------------
	//パラメータ初期化
	void DispFrontEnd::ParamInit ( P_Param pParam )
	{
		//ゲーム設定
		GameSettingFile stg = pParam->GetGameSetting ();

		//選択キャラ名前・モードを取得
		PLAYER_MODE playerMode = stg.GetPlayerMode ( m_playerID );

		//プレイヤモード(入力種類)による初期化
		switch ( playerMode )
		{
#if 0
		case MODE_PLAYER: SetPlayer (); break;
		case MODE_CPU: SetCPU (); break;
#endif // 0
		case MODE_NETWORK: break;
		default: break;
		}
	}


#if 0

	void DispFrontEnd::SetPlayer ()
	{
		m_grp_Cst_InputPlayerCOM->SetIndexTexture ( INPUT_PLAYER );
		m_grp_CH_InputCOMPLayer->SetIndexTexture ( INPUT_PLAYER );
	}

	void DispFrontEnd::SetCPU ()
	{
		m_grp_Cst_InputPlayerCOM->SetIndexTexture ( INPUT_CPU );
		m_grp_CH_InputCOMPLayer->SetIndexTexture ( INPUT_CPU );
	}

#endif // 0


	//------------------------
	//更新

	//ゲージ
	void DispFrontEnd::UpdateGauge ( BtlParam btlPrm )
	{
		//ライフ
//		int white = btlPrm.GetWhiteDamage ();
		m_gaugeLife->Update ( btlPrm.GetLife () );
		m_gaugeLife->UpdateWhite ( btlPrm.GetWhiteDamage () );

		//バランス上限値変更
		float w = btlPrm.GetBalanceMax() / (1.f * (int32)BALANCE_MAX) * 100.f;
		m_gaugeBalance->ChangeMax ( w );
		m_gaugeBalance->Update ( btlPrm.GetBalance () );

		//マナ
		m_gaugeMana->Update ( btlPrm.GetMana () );

		//アクセル
		m_gaugeAccel->Update ( btlPrm.GetAccel () );
	}

	void DispFrontEnd::UpdateMainImage ( VEC2 posChara )
	{
		//プレイヤー表示
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//基準位置
		VEC2 vecImgPlayer = VEC2 ( bx, 0 ) + posChara + VEC2 ( -32.f, 0 );
		vecImgPlayer.y = 32.f + 1.f * (int32)PLAYER_BASE_Y;	//y方向のみ指定

#if 0
		m_grp_CH_Player1P2P->SetPos(vecImgPlayer);
		m_grp_CH_InputCOMPLayer->SetPos ( vecImgPlayer + VEC2 ( 0, 33 ) );
#endif // 0

		//硬直時間表示
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//ヒットストップ時間
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//のけぞり時間
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

	}


	//ヒット数
	void DispFrontEnd::UpdateHitNum ( UINT n )
	{
		if ( n < 0 || 100 <= n ) { return; }

		int n1 = n % 10;	//1桁目
		int n2 = (n / 10) % 10;	//2桁目
		P_Ob pOb = m_grpHitNum->GetpObject ( 1 );

		m_grpHitNum->SetIndexTexture ( n1 );

		if ( n < 2 )
		{
			m_grpHitNum->SetValid ( F );
			m_grpStrHit->SetValid ( F );
		}
		else
		{
			m_grpHitNum->SetValid ( T );
			m_grpStrHit->SetValid ( T );
			if ( n < 10 )
			{
				pOb->SetValid ( F );
			}
			else
			{
				pOb->SetIndexTexture ( n2 );
				pOb->SetValid ( T );
			}
		}
	}

	//-------------------------------------------------------------------
	//状態表示
	void DispFrontEnd::UpdateActionName ( s3d::String actionName )
	{
		m_strAction->SetStr ( actionName );
//		m_strAction->Draw ();
	}

	void DispFrontEnd::UpdateStateName ( s3d::String stateName )
	{
		m_strState->SetStr ( stateName );
	}


#if 0
	void DispChara::UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT hitstop, UINT hitstopTimer )
	{
		//のけぞりフレーム時間表示
		float fLurch = 10 * ( (float)hitstop - hitstopTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeHitStop.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 ), ptChara.y - fLurch, 10.f, fLurch );
	}

	void DispChara::UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer )
	{
		//のけぞりフレーム時間表示
		float fLurch = 10 * ( (float)lurch - lurchTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeLurch.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 ), ptChara.y - fLurch, 10.f, fLurch );
	}
#endif	//0

#if 0

	//ヒット
	void DispChara::OnHit ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpHitEf.SetWait ( 15 );
		m_grpHitEf.SetFadeOut ( 15 );

		//向きによる位置の計算
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -128 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara;
//		m_grpHitEf.GetpMatrix()->SetPos ( img_vec );
		m_grpHitEf.SetPos ( ptChara + VEC2 ( 0, -128 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpHitEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpHitEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpHitEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpHitEf.On ();
	}

	//アヴォイド
	void DispChara::OnAvoid ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpAvoidEf.SetWait ( 15 );
		m_grpAvoidEf.SetFadeIn ( 15 );

		//向きによる位置の計算
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( -128, -256 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -64 );
//		m_grpAvoidEf.GetpMatrix()->SetPos ( img_vec );
//		m_grpAvoidEf.SetPos ( img_vec );
		m_grpAvoidEf.SetPos ( ptChara + VEC2 ( 0, -64 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpAvoidEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpAvoidEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpAvoidEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpAvoidEf.On ();
	}

	//ポイズド
	void DispChara::OnPoised ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpPoisedEf.SetWait ( 15 );
		m_grpPoisedEf.SetFadeIn ( 15 );

		//位置の計算
		m_grpPoisedEf.SetPos ( ptChara + VEC2 ( 0, -96 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpPoisedEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpPoisedEf.SetTargetScaling ( VEC2 ( dir * 1.5f, 1.5f ) );
		m_grpPoisedEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpPoisedEf.On ();
	}


#endif // 0


	void DispFrontEnd::On ()
	{
		m_gaugeLife->On ();
		m_gaugeBalance->On ();
		m_gaugeMana->On ();

		m_strAction->SetValid ( T );
		m_strState->SetValid ( T );
		m_gaugeAccel->On ();
#if 0
		m_grp_Cst_Player1P2P->SetValid ( T );
		m_grp_Cst_InputPlayerCOM->SetValid ( T );

		m_grp_CH_Player1P2P->SetValid ( T );
		m_grp_CH_InputCOMPLayer->SetValid ( T );
#endif // 0

	}

	void DispFrontEnd::Off ()
	{
		m_gaugeLife->Off ();
		m_gaugeBalance->Off ();
		m_gaugeMana->Off ();

		m_strAction->SetValid ( F );
		m_strState->SetValid ( F );

		m_gaugeAccel->Off ();
#if 0
		m_grp_Cst_Player1P2P->SetValid ( F );
		m_grp_Cst_InputPlayerCOM->SetValid ( F );

		m_grp_CH_Player1P2P->SetValid ( F );
		m_grp_CH_InputCOMPLayer->SetValid ( F );
#endif // 0

	}


}	//namespace GAME

