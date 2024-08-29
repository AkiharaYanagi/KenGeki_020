//=================================================================================================
//
//	CharaSele Player ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Player.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//---------------------------------------------------------
	// @info	switch文の条件に用いるとき、externで別ファイルに記述するとコンパイルエラーとなるので
	//			同ファイルに記述する。
	//---------------------------------------------------------
	//キャラ枠位置( 0 ~ 11 )
	const CHARA_SELE_ID		 CHSLID_00 = 0;
	const CHARA_SELE_ID		 CHSLID_01 = 1;
	const CHARA_SELE_ID		 CHSLID_02 = 2;
	const CHARA_SELE_ID		 CHSLID_03 = 3;
	const CHARA_SELE_ID		 CHSLID_04 = 4;
	const CHARA_SELE_ID		 CHSLID_05 = 5;
	const CHARA_SELE_ID		 CHSLID_06 = 6;
	const CHARA_SELE_ID		 CHSLID_07 = 7;
	const CHARA_SELE_ID		 CHSLID_08 = 8;
	const CHARA_SELE_ID		 CHSLID_09 = 9;
	const CHARA_SELE_ID		 CHSLID_10 = 10;
	const CHARA_SELE_ID		 CHSLID_11 = 11;

	//	const CHARA_SELE_ID		 CHARA_SELE_NUM = 12;
	//	const CHARA_SELE_ID	CharaSele_Player::CHARA_SELE_NUM = 12;




	CharaSele_Player::CharaSele_Player ()
	{
		//キャラ立絵
		m_chara_stand = std::make_shared < GameGraphic > ();
		m_chara_stand->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka.png" );
		m_chara_stand->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_stand->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae.png" );
		AddpTask ( m_chara_stand );
		GRPLST_INSERT ( m_chara_stand );

		//キャラ立絵(明度)
		m_chara_stand_light = std::make_shared < GameGraphic > ();
		m_chara_stand_light->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka_light.png" );
		m_chara_stand_light->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_stand_light->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae_light.png" );
		AddpTask ( m_chara_stand_light );
		GRPLST_INSERT ( m_chara_stand_light );
		m_chara_stand_light->SetValid ( F );

		//キャラ名前
		m_chara_name = std::make_shared < GameGraphic > ();
		m_chara_name->AddTexture_FromArchive ( U"Name_Ouka.png" );
		m_chara_name->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_name->AddTexture_FromArchive ( U"Name_Sae.png" );
		AddpTask ( m_chara_name );
		GRPLST_INSERT ( m_chara_name );

		//カーソル
		m_cursor = std::make_shared < GrpBlink > ();
		m_cursor->AddTexture_FromArchive ( U"CharaSele_Cursor_1p.png" );
		m_cursor->AddTexture_FromArchive ( U"CharaSele_Cursor_2p.png" );
		m_cursor->SetTimer ( 15 );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );
	}

	CharaSele_Player::~CharaSele_Player ()
	{
	}

	void CharaSele_Player::PlayerInit ( PLAYER_ID id )
	{
		m_player_id = id;

		if ( PLAYER_ID_1 == id )
		{
			m_chsl_id = CHSLID_00;
			m_x = CHARA_1P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
			m_chara_stand->SetIndexTexture ( CHSLID_00 );
			m_chara_stand_light->SetPos ( m_x, CHARA_1P_POS_Y );
			m_chara_stand_light->SetIndexTexture ( CHSLID_00 );
			m_chara_name->SetPos ( CHARA_NAME_1P_X, CHARA_NAME_1P_Y );
			m_cursor->SetPos ( SELECT_1P_POS_X, SELECT_1P_POS_Y );
			m_cursor->SetIndexTexture ( 0 );
		}
		else if ( PLAYER_ID_2 == id )
		{
			m_chsl_id = CHSLID_02;
			m_x = CHARA_2P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
			m_chara_stand->SetIndexTexture ( CHSLID_02 );
			m_chara_stand_light->SetPos ( m_x, CHARA_2P_POS_Y );
			m_chara_stand_light->SetIndexTexture ( CHSLID_02 );
			m_chara_name->SetPos ( CHARA_NAME_2P_X, CHARA_NAME_2P_Y );
			m_cursor->SetPos ( SELECT_2P_POS_X, SELECT_2P_POS_Y );
			m_cursor->SetIndexTexture ( 1 );
		}
	}

	void CharaSele_Player::Move ()
	{
		//入力
		if ( m_decided )	//決定済みならば
		{
			Input_Decided ();	//キャンセルのみ
		}
		else
		{
			Input ();	//移動と決定
		}

		//選択キャラ表示
		switch ( m_chsl_id )
		{
		case CHSLID_00: SetCharaStand ( CHSLID_00 ); break;
		case CHSLID_01: HiddenCharaStand ();break;
		case CHSLID_02: SetCharaStand ( CHSLID_02 ); break;
		case CHSLID_03: HiddenCharaStand ();break;
		case CHSLID_04: HiddenCharaStand ();break;
		case CHSLID_05: HiddenCharaStand ();break;
		case CHSLID_06: HiddenCharaStand ();break;
		case CHSLID_07: HiddenCharaStand ();break;
		case CHSLID_08: HiddenCharaStand ();break;
		case CHSLID_09: HiddenCharaStand ();break;
		default: break;
		}

		//選択カットイン
		if ( PLAYER_ID_1 == m_player_id )
		{
			if ( m_x < (int32)CHARA_1P_POS_X )
			{
				m_x += (int32)CUTIN_VX; 
				m_chara_stand->SetPos ( m_x, (float)CHARA_1P_POS_Y );
			}
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			if ( (int32)CHARA_2P_POS_X < m_x )
			{
				m_x -= (int32)CUTIN_VX; 
				m_chara_stand->SetPos ( m_x, (float)CHARA_2P_POS_Y );
			}
		}

		//決定待機
		if ( ++ m_wait > 10 )
		{
			//明度を戻す
			m_chara_stand_light->SetValid ( F );
			m_wait = 0;
		}

		TASK_VEC::Move ();
	}

	CHARA_NAME CharaSele_Player::GetName () const
	{
		return m_pos[m_chsl_id].Name;
	}



	void CharaSele_Player::SetCursorUp ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		id = m_pos [ id ].UP;
		pCrs->SetPos ( VEC2 ( m_pos [ id ].x, m_pos [ id ].y ) );
		Select ();
	}
	void CharaSele_Player::SetCursorDown ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		id = m_pos [ id ].DOWN;
		pCrs->SetPos ( VEC2 ( m_pos [ id ].x, m_pos [ id ].y ) );
		Select ();
	}
	void CharaSele_Player::SetCursorLeft ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		id = m_pos [ id ].LEFT;
		pCrs->SetPos ( VEC2 ( m_pos [ id ].x, m_pos [ id ].y ) );
		Select ();
	}
	void CharaSele_Player::SetCursorRight ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		id = m_pos [ id ].RIGHT;
		pCrs->SetPos ( VEC2 ( m_pos [ id ].x, m_pos [ id ].y ) );
		Select ();
	}


	//-------------------------------------------------------------------
	// 
	//入力
	void CharaSele_Player::Input ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			//移動
			if ( CFG_PUSH_KEY ( P1_UP ) ) { SetCursorUp ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P1_DOWN ) ) { SetCursorDown ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P1_LEFT ) ) { SetCursorLeft ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P1_RIGHT ) ) { SetCursorRight ( m_cursor, m_chsl_id ); }

			//決定
			if ( CFG_PUSH_KEY ( P1_BTN0 ) ) { Decide (); }
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			if ( CFG_PUSH_KEY ( P2_UP ) ) { SetCursorUp ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P2_DOWN ) ) { SetCursorDown ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P2_LEFT ) ) { SetCursorLeft ( m_cursor, m_chsl_id ); }
			if ( CFG_PUSH_KEY ( P2_RIGHT ) ) { SetCursorRight ( m_cursor, m_chsl_id ); }

			//決定
			if ( CFG_PUSH_KEY ( P2_BTN0 ) ) { Decide (); }
		}
	}


	void CharaSele_Player::Input_Decided ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			if ( CFG_PUSH_KEY ( P1_BTN1 ) )
			{
				Cancel ();	//否定
			}
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			if ( CFG_PUSH_KEY ( P2_BTN1 ) )
			{
				Cancel ();	//否定
			}
		}
	}


	//キャンセル
	void CharaSele_Player::Cancel ()
	{
		m_decided = F;
		m_chara_stand->SetValid ( T );
		m_chara_stand_light->SetValid ( F );
		m_cursor->Start ();
		SOUND->Play_SE ( SE_Sys_Cancel );
		m_wait = 0;
	}


	//カーソル移動で選択時
	void CharaSele_Player::Select ()
	{
		//選択カットイン
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_x -= (float)CUTIN_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_x += (float)CUTIN_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
		}

		SOUND->Play_SE ( SE_Sys_Select );
	}

	//決定時
	void CharaSele_Player::Decide ()
	{
		//選択可能かどうか
		if ( ! CanSelect () )
		{
			SOUND->Play_SE ( SE_Sys_Lock );
			return;
		}

		m_decided = T; 
		m_chara_stand->SetValid ( F );
		m_chara_stand_light->SetValid ( T );
		m_cursor->Stop ();
		SOUND->Play_SE ( SE_Sys_Enter );
		m_wait = 1;	//待機スタート
	}


	//選択可能かどうか
	bool CharaSele_Player::CanSelect ()
	{
		switch ( m_chsl_id )
		{
		case CHSLID_00: return T;
		case CHSLID_01: break;
		case CHSLID_02: return T;
		case CHSLID_03: break;
		case CHSLID_04: break;
		case CHSLID_05: break;
		case CHSLID_06: break;
		case CHSLID_07: break;
		case CHSLID_08: break;
		case CHSLID_09: break;
		default: break;
		}
		return F;
	}

	void CharaSele_Player::SetCharaStand ( CHARA_SELE_ID id )
	{
		m_chara_stand->SetValid ( T );
		m_chara_stand->SetIndexTexture ( id ); 
		m_chara_stand_light->SetIndexTexture ( id ); 
		m_chara_name->SetValid ( T );
		m_chara_name->SetIndexTexture ( id );
	}


	void CharaSele_Player::HiddenCharaStand ()
	{
		m_chara_stand->SetValid ( F ); 
		m_chara_name->SetValid ( F );
	}


}	//namespace GAME

