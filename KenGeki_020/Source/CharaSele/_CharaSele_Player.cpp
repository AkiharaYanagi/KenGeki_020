//=================================================================================================
//
//	_CharaSele Player ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele_Player.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	_CharaSele_Player::_CharaSele_Player ()
	{
		//状態表示
		m_state_Disp = std::make_shared < GrpBlink > ();
		m_state_Disp->SetBlinkTime ( 20 );
		m_state_Disp->SetHalf ( T );
		m_state_Disp->SetZ ( Z_MENU );
		AddpTask ( m_state_Disp );
		GRPLST_INSERT ( m_state_Disp );

		//カラーセレクト文字表示
		m_txt_ClrSl = std::make_shared < GrpBlink > ();
		m_txt_ClrSl->AddTexture_FromArchive ( U"CharaSele\\Text_COLOR_SELECT.png" );
		m_txt_ClrSl->SetZ ( Z_SYS );
		m_txt_ClrSl->Stop ();
		m_txt_ClrSl->SetHalf ( T );
		AddpTask ( m_txt_ClrSl );
		GRPLST_INSERT ( m_txt_ClrSl );

		//カラーセレクト矢印表示
		m_Arw_ClrSl = std::make_shared < GrpBlink > ();
		m_Arw_ClrSl->AddTexture_FromArchive ( U"CharaSele\\SelectTriangleColor.png" );
		m_Arw_ClrSl->SetZ ( Z_SYS );
		m_Arw_ClrSl->Stop ();
		m_Arw_ClrSl->SetHalf ( T );
		AddpTask ( m_Arw_ClrSl );
		GRPLST_INSERT ( m_Arw_ClrSl );

		//カラーセレクト番号表示
		m_Num_ClrSl = std::make_shared < GameGraphic > ();
		m_Num_ClrSl->AddTexture_FromArchive ( U"CharaSele\\Color1.png" );
		m_Num_ClrSl->AddTexture_FromArchive ( U"CharaSele\\Color2.png" );
		m_Num_ClrSl->SetZ ( Z_SYS );
		AddpTask ( m_Num_ClrSl );
		GRPLST_INSERT ( m_Num_ClrSl );

		//カーソル
		m_cursor = std::make_shared < CharaSele_Cursor > ();
		AddpTask ( m_cursor );

		//キャラ立ち絵
		m_chara_img = std::make_shared < CharaSele_Image > ();


		//状態アクタ
		m_actor = std::make_shared < _CharaSele_Actor > ();
		m_actor->SetpCursor ( m_cursor );

	}

	_CharaSele_Player::~_CharaSele_Player ()
	{
	}

	void _CharaSele_Player::LoadTx ( P_ChSl_Img_Cmn pCmn )
	{
		m_chara_img->LoadTx ( pCmn );
	}

	void _CharaSele_Player::PlayerInit ( PLAYER_ID id )
	{
		m_player_id = id;

		m_actor->PlayerInit ( id );
		m_cursor->PlayerInit ( id );
		m_chara_img->PlayerInit ( id );

		//プレイヤ側別初期位置
		if ( PLAYER_ID_1 == id )
		{
//			m_chsl_id = CHSLID_00;
			m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\1P_State.png" );
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_CHARA_Y );
			m_txt_ClrSl->SetPos ( VEC2 ( TXT_CLR_SL_1P_X, TXT_CLR_SL_Y ) );
			m_Arw_ClrSl->SetPos ( VEC2 ( ARW_CLR_SL_1P_X, ARW_CLR_SL_Y ) );
			m_Num_ClrSl->SetPos ( VEC2 ( NUM_CLR_SL_1P_X, NUM_CLR_SL_Y ) );
#if 0
			m_grp_Cst_InputPlayerCOM->SetPos ( 300, 5 );
#endif // 0
		}
		else if ( PLAYER_ID_2 == id )
		{
//			m_chsl_id = CHSLID_02;
			m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\2P_State.png" );
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_CHARA_Y );
			m_txt_ClrSl->SetPos ( VEC2 ( TXT_CLR_SL_2P_X, TXT_CLR_SL_Y ) );
			m_Arw_ClrSl->SetPos ( VEC2 ( ARW_CLR_SL_2P_X, ARW_CLR_SL_Y ) );
			m_Num_ClrSl->SetPos ( VEC2 ( NUM_CLR_SL_2P_X, NUM_CLR_SL_Y ) );
#if 0
			m_grp_Cst_InputPlayerCOM->SetPos ( 1280 - 64 - 300, 5 );
#endif // 0
		}
	}

	void _CharaSele_Player::ParamInit ( P_Param prm )
	{
		AssignName ( prm->GetCharaName ( m_player_id ) );
		SelectColor ( prm->GetCharaColor ( m_player_id ) );

#if 0
		//プレイヤ側別初期化
		if ( PLAYER_ID_1 == m_player_id )
		{
			AssignName ( prm->GetCharaName1p () );
			SelectColor ( prm->GetCharaColor1p () );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			AssignName ( prm->GetCharaName2p () );
			SelectColor ( prm->GetCharaColor2p () );
		}
#endif // 0

		//test
		//カラーを１に戻す
		SelectColor ( CH_CLR_1 );

	}


	void _CharaSele_Player::Load ()
	{
		m_actor->SetwpChSl_Player ( shared_from_this () );
		m_actor->Load ();

		m_cursor->SetwpChSl_Player ( shared_from_this () );
	}

	void _CharaSele_Player::Move ()
	{
		m_actor->Move ();
		m_chara_img->Move ();

		TASK_VEC::Move ();
	}

	void _CharaSele_Player::Input ()
	{
		m_actor->Input ();
	}

	void _CharaSele_Player::SelectChara_cutin ( CHARA_SELE_ID chara_id )
	{
//		m_chsl_id = chara_id;
		m_chara_img->SelectChara_cutin ( chara_id );
	}

	void _CharaSele_Player::SelectChara ( CHARA_SELE_ID chara_id )
	{
//		m_chsl_id = chara_id;
		m_chara_img->SelectChara ( chara_id );
	}

	CHARA_NAME _CharaSele_Player::GetCharaName () const
	{
		return m_cursor->GetCharaName ();
	}


	void _CharaSele_Player::SelectColor_cutin ( CHARA_COLOR chara_clr )
	{
		m_color = chara_clr;
		m_chara_img->SetColor_cutin ( chara_clr );
		m_Num_ClrSl->SetIndexTexture ( chara_clr );
	}

	void _CharaSele_Player::SelectColor ( CHARA_COLOR chara_clr )
	{
		m_color = chara_clr;
		m_chara_img->SetColor ( chara_clr );
		m_Num_ClrSl->SetIndexTexture ( chara_clr );
	}



	void _CharaSele_Player::To_Chara ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_CHARA_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_CHARA_Y );
		}

		//カラーを１に戻す
		SelectColor ( CH_CLR_1 );

		m_cursor->Start ();
	}



	void _CharaSele_Player::To_Color ()
	{

		//test
		//カラーを１に戻す
		SelectColor ( CH_CLR_1 );


		if ( PLAYER_ID_1 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_COLOR_1P_X, CH_STT_COLOR_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_COLOR_2P_X, CH_STT_COLOR_Y );
		}

		m_cursor->Stop ();
	}

	void _CharaSele_Player::To_Stage ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_STAGE_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_STAGE_Y );
		}
	}

	void _CharaSele_Player::To_BGM ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_BGM_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_BGM_Y );
		}
	}

	void _CharaSele_Player::To_OK ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_OK_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_OK_Y );
		}
	}

	//キャラ名から選択する
	void _CharaSele_Player::AssignName ( CHARA_NAME name )
	{
//		m_chsl_id = CharaName_To_ChSlId ( name );
		CHARA_SELE_ID id = CharaName_To_ChSlId ( name );
		SelectChara ( id );
		m_cursor->SetChara ( id );
	}


#pragma region CONST
	//選択状態カーソル位置
	const float _CharaSele_Player::CH_STT_X_1P = 403;
	const float _CharaSele_Player::CH_STT_X_2P = 406;
	const float _CharaSele_Player::CH_STT_CHARA_Y = 8;
	const float _CharaSele_Player::CH_STT_COLOR_1P_X = 80 - 70;
	const float _CharaSele_Player::CH_STT_COLOR_2P_X = 800;
	const float _CharaSele_Player::CH_STT_COLOR_Y = 850;
	const float _CharaSele_Player::CH_STT_STAGE_Y = 370;
	const float _CharaSele_Player::CH_STT_BGM_Y = 552;
	const float _CharaSele_Player::CH_STT_OK_Y = 2000;	//画面外

	//カラーセレクト文字表示
	const float _CharaSele_Player::TXT_CLR_SL_1P_X = 112;
	const float _CharaSele_Player::TXT_CLR_SL_2P_X = 1280 - 220 - TXT_CLR_SL_1P_X;
	const float _CharaSele_Player::TXT_CLR_SL_Y = 865;

	//カラーセレクト矢印表示
	const float _CharaSele_Player::ARW_CLR_SL_1P_X = 124;
	const float _CharaSele_Player::ARW_CLR_SL_2P_X = 1280 - 198 - ARW_CLR_SL_1P_X;
	const float _CharaSele_Player::ARW_CLR_SL_Y = TXT_CLR_SL_Y + 30;

	//カラーセレクト番号表示
	const float _CharaSele_Player::NUM_CLR_SL_1P_X = 156;
	const float _CharaSele_Player::NUM_CLR_SL_2P_X = 1280 - 130 - NUM_CLR_SL_1P_X;
	const float _CharaSele_Player::NUM_CLR_SL_Y = TXT_CLR_SL_Y + 40;

	//操作 PLAYER/CPU
	const uint32 _CharaSele_Player::PLAYER = 0;
	const uint32 _CharaSele_Player::CPU = 1;
#pragma endregion


}	//namespace GAME

