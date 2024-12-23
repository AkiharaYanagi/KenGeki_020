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
	VEC2 const DispFrontEnd::POS_PL_CP_1P ( 5, LIFE_GAUGE_Y );
	VEC2 const DispFrontEnd::POS_PL_CP_2P ( 1280 - 64 - 5, LIFE_GAUGE_Y );
	const float DispFrontEnd::FACE_X = 80;
	const float DispFrontEnd::FACE_Y = 840;
	const float DispFrontEnd::FACE_W = 100;
	const float DispFrontEnd::CHOU_X = 326;
	const float DispFrontEnd::CHOU_Y = 850;
	const float DispFrontEnd::CHOU_W = 100;

	const float DispFrontEnd::NAME_BG_X = 155;
	const float DispFrontEnd::NAME_BG_Y = 900;
	const float DispFrontEnd::NAME_BG_W = 256;

	const float DispFrontEnd::NAME_X = 175;
	const float DispFrontEnd::NAME_Y = 913;

	const float DispFrontEnd::DMG_X = 50;
	const float DispFrontEnd::DMG_Y = 180;

	//各ファイルサイズから幅を指定
	const float DispFrontEnd::NAME_W[3] = { 167.f, 118.f, 179.f };


	//@todo Z値のまとめ


	DispFrontEnd::DispFrontEnd ()
	{
		//ゲージ類

		//ライフゲージ
		m_gaugeLife = std::make_shared < DispGauge > ();
		m_gaugeLife->SetPosition ( LIFE_GAUGE_X, LIFE_GAUGE_Y, LIFE_GAUGE_W, LIFE_GAUGE_H );
		m_gaugeLife->SetPadding ( LIFE_GAUGE_P );
		m_gaugeLife->SetZ ( Z_SHADOW );
		m_gaugeLife->SetTextureName_Frame ( U"Battle\\gauge_life_frame_2p.png" );
		m_gaugeLife->SetTextureName_Value ( U"Battle\\gauge_life_value_2p.png" );
		m_gaugeLife->SetTextureName_Decrease ( U"Battle\\gauge_life_decrease_2p.png" );
		m_gaugeLife->SetTextureName_White ( U"Battle\\gauge_life_white_2p.png" );
//	m_gaugeLife->SetColor_Decrease ( LIFE_GAUGE_DECREASE_CLR );
		m_gaugeLife->OnWhite ();
		AddpTask ( m_gaugeLife );

		//バランスゲージ
		m_gaugeBalance = std::make_shared < DispGauge > ();
		m_gaugeBalance->SetPosition ( BALANCE_GAUGE_X, BALANCE_GAUGE_Y, BALANCE_GAUGE_W, BALANCE_GAUGE_H );
		m_gaugeBalance->SetPadding ( BALANCE_GAUGE_P );
		m_gaugeBalance->SetZ ( Z_SHADOW );
		m_gaugeBalance->SetTextureName_Frame ( U"Battle\\gauge_balance_frame.png" );
		m_gaugeBalance->SetTextureName_Value ( U"Battle\\gauge_balance_value.png" );
		m_gaugeBalance->OffDecrease ();
		m_gaugeBalance->OffWhite ();
		AddpTask ( m_gaugeBalance );

		//マナゲージ
		m_gaugeMana = std::make_shared < DispGauge > ();
		m_gaugeMana->SetPosition ( MANA_GAUGE_X, MANA_GAUGE_Y, MANA_GAUGE_W, MANA_GAUGE_H );
		m_gaugeMana->SetPadding ( MANA_GAUGE_P );
		m_gaugeMana->SetZ ( Z_SYS );
		m_gaugeMana->SetTextureName_Frame ( U"Battle\\gauge_mana_frame.png" );
		m_gaugeMana->SetTextureName_Value ( U"Battle\\gauge_mana_value.png" );
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
		m_grp_Cst_Player1P2P = MakepGrpPlyr ( U"Player_1P.png" );
		m_grp_Cst_Player1P2P->AddTexture_FromArchive ( U"Player_2P.png" );

		m_grp_Cst_InputPlayerCOM = MakepGrpPlyr ( U"INPUT_PLAYER.png" );
		m_grp_Cst_InputPlayerCOM->AddTexture_FromArchive ( U"INPUT_CPU.png" );

		m_grp_CH_Player1P2P = MakepGrpPlyr ( U"Player_1P.png" );
		m_grp_CH_Player1P2P->AddTexture_FromArchive ( U"Player_2P.png" );

		m_grp_CH_InputCOMPLayer = MakepGrpPlyr ( U"INPUT_PLAYER.png" );
		m_grp_CH_InputCOMPLayer->AddTexture_FromArchive ( U"INPUT_CPU.png" );
#if 0

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

		//-----------------------------------------
		//ダメージ
		m_strDmg = std::make_shared < GrpStr > ();
		m_strDmg->SetSize ( G_Font::SIZE_30 );
		m_strDmg->SetZ ( Z_SYS - 0.01f );
		m_strDmg->SetValid ( F );
		AddpTask ( m_strDmg );
		GRPLST_INSERT ( m_strDmg );

		//-----------------------------------------
		//補正
		m_strRevise = std::make_shared < GrpStr > ();
		m_strRevise->SetSize ( G_Font::SIZE_30 );
		m_strRevise->SetZ ( Z_SYS - 0.01f );
		m_strRevise->SetValid ( F );
		AddpTask ( m_strRevise );
		GRPLST_INSERT ( m_strRevise );


		//------------------------------------------------------
		//アクション名
		m_strAction = std::make_shared < GrpStr > ();
		m_strAction->SetStr ( U"Action" );
		m_strAction->SetZ ( Z_SYS );
		m_strAction->SetSize ( G_Font::SIZE_40 );
		m_strAction->SetColorF ( s3d::ColorF { 0.8f, 0.8f, 1.f, 1.f } );
		AddpTask ( m_strAction );
		GRPLST_INSERT ( m_strAction );

		//ステート名
		m_strState = std::make_shared < GrpStr > ();
		m_strState->SetStr ( U"State" );
		m_strState->SetZ ( Z_SYS );
		m_strState->SetSize ( G_Font::SIZE_40 );
		m_strState->SetColorF ( s3d::ColorF { 0.0f, 0.0f, 0.5f, 1.f } );
		AddpTask ( m_strState );
		GRPLST_INSERT ( m_strState );

		//名前背景
		m_name_bg = std::make_shared < GameGraphic > ();
		m_name_bg->AddTexture_FromArchive ( U"Battle\\Name_BG.png" );
		m_name_bg->SetZ ( Z_SHADOW );
		m_name_bg->SetScalingCenter ( VEC2 ( NAME_BG_W / 2, 18 ) );
		GRPLST_INSERT ( m_name_bg );
		AddpTask ( m_name_bg );

		//顔
		m_face = std::make_shared < GameGraphic > ();
		m_face->AddTexture_FromArchive ( U"Battle\\Face_Ouka.png" );
		m_face->AddTexture_FromArchive ( U"Battle\\Face_Sae.png" );
		m_face->AddTexture_FromArchive ( U"Battle\\Face_Retsudou.png" );
		m_face->SetIndexTexture ( 0 );
		m_face->SetZ ( Z_SHADOW + 0.01f );
		AddpTask ( m_face );
		GRPLST_INSERT ( m_face );

		//超必殺
		m_ChouHissatsu = std::make_shared < GameGraphic > ();
		m_ChouHissatsu->AddTexture_FromArchive ( U"Battle\\ChouHissatsu.png" );
		m_ChouHissatsu->SetZ ( Z_SYS );
		AddpTask ( m_ChouHissatsu );
		GRPLST_INSERT ( m_ChouHissatsu );

		//名前
		m_name = std::make_shared < GameGraphic > ();
		m_name->AddTexture_FromArchive ( U"Battle\\Name_HIYODORI_OUKA.png" );
		m_name->AddTexture_FromArchive ( U"Battle\\Name_TOMOE_SAE.png" );
		m_name->AddTexture_FromArchive ( U"Battle\\Name_REKKA_RETSUDOU.png" );
		m_name->SetZ ( Z_SYS - 0.01f );
		AddpTask ( m_name );
		GRPLST_INSERT ( m_name );

		//-----------------------------------------
		//剣撃抗圧
		m_kouatsu = std::make_shared < EfKouAtsu > ();
		AddpTask ( m_kouatsu );
		GRPLST_INSERT ( m_kouatsu );
	}

	//オブジェクト生成用
	P_Grp DispFrontEnd::MakepGrpPlyr ( s3d::String str )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->SetValid ( T );
		p->AddTexture_FromArchive ( str );
		p->SetZ ( Z_SYS - 0.06f );
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

		//初期値はOff -> MutualUtilityで指定
		//Off ();

		TASK_VEC::Load ();
	}


	void DispFrontEnd::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		m_gaugeLife->LoadPlayer ( playerID );
		m_gaugeBalance->LoadPlayer ( playerID );
		m_gaugeMana->LoadPlayer ( playerID );
		m_gaugeAccel->LoadPlayer ( playerID );


		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_grp_Cst_Player1P2P->SetPos ( POS_PL_CP_1P );
			m_grp_Cst_Player1P2P->SetIndexTexture ( SIDE_1P );
			m_grp_Cst_InputPlayerCOM->SetPos ( POS_PL_CP_1P + VEC2 ( 0, 18 ) );
			m_grp_CH_Player1P2P->SetIndexTexture ( SIDE_1P );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_grp_Cst_Player1P2P->SetPos ( POS_PL_CP_2P );
			m_grp_Cst_Player1P2P->SetIndexTexture ( SIDE_2P );
			m_grp_Cst_InputPlayerCOM->SetPos ( POS_PL_CP_2P + VEC2 ( 0, 18 ) );
			m_grp_CH_Player1P2P->SetIndexTexture ( SIDE_2P );
		}

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
			m_strDmg->SetPos ( VEC2 ( DMG_X, DMG_Y ) );
			m_strDmg->SetStr ( U"P1_Dmg" );
			m_strRevise->SetPos ( VEC2 ( DMG_X, DMG_Y - 30 ) );
			m_strRevise->SetStr ( U"P1_Revise" );
			
			pOb->SetPos ( VEC2 ( 0, 200 ) );

			m_name_bg->SetPos ( VEC2 ( NAME_BG_X, NAME_BG_Y ) );
			m_name_bg->SetScaling ( VEC2 ( -1.f, 1.f ) );
			m_face->SetPos ( VEC2 ( FACE_X, FACE_Y ) );
			m_ChouHissatsu->SetPos ( VEC2 ( CHOU_X, CHOU_Y ) );
			m_name->SetPos ( VEC2 ( NAME_X, NAME_Y ) );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_grpHitNum->SetPos ( VEC2 ( WINDOW_WIDTH - 384 -100, 200 ) );
			m_grpStrHit->SetPos ( VEC2 ( WINDOW_WIDTH - 256 -100, 200 ) );
			m_strDmg->SetPos ( VEC2 ( WINDOW_WIDTH - 250, DMG_Y ) );
			m_strDmg->SetStr ( U"P2_Dmg" );
			m_strRevise->SetPos ( VEC2 (  WINDOW_WIDTH - 250, DMG_Y - 30 ) );
			m_strRevise->SetStr ( U"P2_Revise" );

			pOb->SetPos ( VEC2 (  WINDOW_WIDTH - 384 - 200, 200 ) );

			m_name_bg->SetPos ( VEC2 ( WINDOW_WIDTH - NAME_BG_W - NAME_BG_X, NAME_BG_Y ) );
			m_face->SetPos ( VEC2 ( WINDOW_WIDTH - FACE_W - FACE_X, FACE_Y ) );
			m_ChouHissatsu->SetPos ( VEC2 ( WINDOW_WIDTH - CHOU_W - CHOU_X, CHOU_Y ) );

			//キャラ名によって幅が異なる
			float w = NAME_W [ - 1 + (int)m_chara_name ];
			m_name->SetPos ( VEC2 (  WINDOW_WIDTH - w - NAME_X, NAME_Y ) );
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

		//選択キャラ名前
		CHARA_NAME charaName = stg.GetName ( m_playerID );
		m_chara_name = charaName;

		//キャラ名による初期化
		switch ( charaName )
		{
		case CHARA_OUKA: break;
		case CHARA_SAE: break;
		case CHARA_RETSUDOU: break;
		default: charaName = CHARA_OUKA; break;
		}
		m_face->SetIndexTexture ( (uint32)charaName - 1 );
		m_name->SetIndexTexture ( (uint32)charaName - 1 );


		//プレイヤモード(入力種類)による初期化
		// 
		//モードを取得
		PLAYER_MODE playerMode = stg.GetPlayerMode ( m_playerID );
		switch ( playerMode )
		{
		case MODE_PLAYER: SetPlayer (); break;
		case MODE_CPU: SetCPU (); break;
#if 0
#endif // 0
		case MODE_NETWORK: break;
		default: break;
		}
	}



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

#if 0
#endif // 0


	//------------------------
	//更新

	//ゲージ
	void DispFrontEnd::UpdateGauge ( const BtlParam & btlPrm )
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


		//抗圧
		if ( btlPrm.GetKouAtsu () )
		{
			m_kouatsu->On ( btlPrm );
		}
	}

	//ダメージ更新
	void DispFrontEnd::UpdateDamage ( const BtlParam & btlPrm )
	{
		//ダメージ(相手)
		int32 chnDmg = btlPrm.GetChainDamage ();
		m_strDmg->SetStr ( U"{} Damage"_fmt( chnDmg ) );

		//補正
#if 0

		//ヒット数による補正表示
		UINT chain = btlPrm.GetChainHitNum ();
		if ( chain == 1 ) { chain = 0; }		//1hit目は補正なし
		if ( chain > 100 ) { chain = 100; }		//上限100

		float d_revise = ( 100.f - (float)chain ) * 0.01f;	//%に換算
		if ( 10 <= chain ) { d_revise *= d_revise; }	//10hit以降補正
		if ( d_revise < 0 ) { d_revise = 0.01f; }	//０にはしない


		std::ostringstream oss;
		oss << std::fixed << std::setprecision ( 3 ) << d_revise * 100;

		m_strRevise->SetStr ( U"{}%"_fmt( s3d::Unicode::Widen ( oss.str() ) ) );

#endif // 0

		m_strRevise->SetStr ( U"{0:.2f}%"_fmt( btlPrm.GetCnfmRvs () * 100 ) );
	}

	void DispFrontEnd::UpdateMainImage ( VEC2 posChara )
	{
		//プレイヤー表示
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//基準位置
		VEC2 vecImgPlayer = VEC2 ( bx, 0 ) + posChara + VEC2 ( -32.f, 0 );
		vecImgPlayer.y = 1.f * (int32)PLAYER_BASE_Y;	//y方向のみ指定

		m_grp_CH_Player1P2P->SetPos(vecImgPlayer);
		m_grp_CH_InputCOMPLayer->SetPos ( vecImgPlayer + VEC2 ( 0, 18 ) );
#if 0
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
	void DispFrontEnd::UpdateHitNum ( const BtlParam & btlPrm )
	{
		int n = btlPrm.GetChainHitNum ();

		if ( n < 0 || 100 <= n ) { return; }

		int n1 = n % 10;	//1桁目
		int n2 = (n / 10) % 10;	//2桁目
		P_Ob pOb = m_grpHitNum->GetpObject ( 1 );

		m_grpHitNum->SetIndexTexture ( n1 );


		//test
		// 
		//1hit以上で表示
		if ( n < 1 )

		//2hit以上で表示
//		if ( n < 2 )
		{
			m_grpHitNum->SetValid ( F );
			m_grpStrHit->SetValid ( F );
			m_strDmg->SetValid ( F );
			m_strRevise->SetValid ( F );
		}
		else
		{
			m_grpHitNum->SetValid ( T );
			m_grpStrHit->SetValid ( T );
			//桁数
			if ( n < 10 )
			{
				pOb->SetValid ( F );
			}
			else
			{
				pOb->SetIndexTexture ( n2 );
				pOb->SetValid ( T );
			}
			m_strDmg->SetValid ( T );
			m_strRevise->SetValid ( T );
		}
	}

	//-------------------------------------------------------------------
	//状態表示
	void DispFrontEnd::UpdateActionName ( s3d::String actionName )
	{
		m_strAction->SetStr ( actionName );
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
#if 0

		m_gaugeLife->On ();
		m_gaugeBalance->On ();
		m_gaugeMana->On ();
		m_gaugeAccel->On ();

		m_name_bg->SetValid ( T );
		m_name->SetValid ( T );
		m_face->SetValid ( T );
		m_ChouHissatsu->SetValid ( T );
#endif // 0

		m_strAction->SetValid ( T );
		m_strState->SetValid ( T );

#if 0
		m_grp_Cst_Player1P2P->SetValid ( T );
		m_grp_Cst_InputPlayerCOM->SetValid ( T );

		m_grp_CH_Player1P2P->SetValid ( T );
		m_grp_CH_InputCOMPLayer->SetValid ( T );
#endif // 0

	}

	void DispFrontEnd::Off ()
	{
#if 0

		m_gaugeLife->Off ();
		m_gaugeBalance->Off ();
		m_gaugeMana->Off ();
		m_gaugeAccel->Off ();

		m_name_bg->SetValid ( F );
		m_name->SetValid ( F );
		m_face->SetValid ( F );
		m_ChouHissatsu->SetValid ( F );
#endif // 0

		m_strAction->SetValid ( F );
		m_strState->SetValid ( F );

#if 0
		m_grp_Cst_Player1P2P->SetValid ( F );
		m_grp_Cst_InputPlayerCOM->SetValid ( F );

		m_grp_CH_Player1P2P->SetValid ( F );
		m_grp_CH_InputCOMPLayer->SetValid ( F );
#endif // 0

	}

	void DispFrontEnd::On_Debug ()
	{
		m_strAction->SetValid ( T );
		m_strState->SetValid ( T );
	}

	void DispFrontEnd::Off_Debug ()
	{
		m_strAction->SetValid ( F );
		m_strState->SetValid ( F );
	}


	void DispFrontEnd::On_DispPlayerInput ()
	{
		m_grp_Cst_Player1P2P->SetValid ( T );
		m_grp_Cst_InputPlayerCOM->SetValid ( T );
		m_grp_CH_Player1P2P->SetValid ( T );
		m_grp_CH_InputCOMPLayer->SetValid ( T );
	}

	void DispFrontEnd::Off_DispPlayerInput ()
	{
		m_grp_Cst_Player1P2P->SetValid ( F );
		m_grp_Cst_InputPlayerCOM->SetValid ( F );
		m_grp_CH_Player1P2P->SetValid ( F );
		m_grp_CH_InputCOMPLayer->SetValid ( F );
	}


	void DispFrontEnd::EndBattle ()
	{
		m_grpHitNum->SetValid ( F );
	}


}	//namespace GAME

