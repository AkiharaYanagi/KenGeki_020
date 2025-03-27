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

#pragma region CONST
	const float _CharaSele_Player::CH_STT_X_1P = 402;
	const float _CharaSele_Player::CH_STT_X_2P = 405;
	const float _CharaSele_Player::CH_STT_CHARA_Y = 8;
	const float _CharaSele_Player::CH_STT_STAGE_Y = 370;
	const float _CharaSele_Player::CH_STT_BGM_Y = 552;
	const float _CharaSele_Player::CH_STT_OK_Y = 2000;	//画面外

	const uint32 _CharaSele_Player::PLAYER = 0;
	const uint32 _CharaSele_Player::CPU = 1;
#pragma endregion



	_CharaSele_Player::_CharaSele_Player ()
	{
		//状態表示
		m_state_Disp = std::make_shared < GrpBlink > ();
		m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\1P_State.png" );
		m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\2P_State.png" );
		m_state_Disp->SetBlinkTime ( 20 );
		m_state_Disp->SetHalf ( T );
		m_state_Disp->SetZ ( Z_MENU );
		AddpTask ( m_state_Disp );
		GRPLST_INSERT ( m_state_Disp );

		//キャラ立ち絵
		m_chara_img = std::make_shared < CharaSele_Image > ();
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

		//キャラ立ち絵
		m_chara_img->PlayerInit ( id );

		//プレイヤ側別初期位置
		if ( PLAYER_ID_1 == id )
		{
			m_chsl_id = CHSLID_00;
			m_state_Disp->SetIndexTexture ( 0 );
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_CHARA_Y );
#if 0

			m_x = CHARA_1P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
			m_chara_stand->SetIndexTexture ( CHSLID_00 );
			m_chara_stand_light->SetPos ( m_x, CHARA_1P_POS_Y );
			m_chara_stand_light->SetIndexTexture ( CHSLID_00 );
			m_chara_name->SetPos ( CHARA_NAME_1P_X, CHARA_NAME_1P_Y );
			m_cursor->SetPos ( VEC2 ( m_pos [ CHSLID_00 ].x, m_pos [ CHSLID_00 ].y ) );
			m_cursor->SetIndexTexture ( 0 );
			m_grp_Cst_InputPlayerCOM->SetPos ( 300, 5 );

#endif // 0
		}
		else if ( PLAYER_ID_2 == id )
		{
			m_chsl_id = CHSLID_02;
			m_state_Disp->SetIndexTexture ( 1 );
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_CHARA_Y );
#if 0
			m_x = CHARA_2P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
			m_chara_stand->SetIndexTexture ( CHSLID_02 );
			m_chara_stand_light->SetPos ( m_x, CHARA_2P_POS_Y );
			m_chara_stand_light->SetIndexTexture ( CHSLID_02 );
			m_chara_name->SetPos ( CHARA_NAME_2P_X, CHARA_NAME_2P_Y );
			m_cursor->SetPos ( VEC2 ( m_pos [ CHSLID_02 ].x, m_pos [ CHSLID_02 ].y ) );
			m_cursor->SetIndexTexture ( 1 );
			m_grp_Cst_InputPlayerCOM->SetPos ( 1280 - 64 - 300, 5 );
#endif // 0
		}
	}

	void _CharaSele_Player::ParamInit ( P_Param prm )
	{
	}

	void _CharaSele_Player::Move ()
	{
		TASK_VEC::Move ();
	}


}	//namespace GAME

