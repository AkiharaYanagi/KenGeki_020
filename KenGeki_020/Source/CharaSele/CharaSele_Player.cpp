//=================================================================================================
//
//	CharaSele Player ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Player.h"
#include "../GameMain/SeConst.h"


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

	const float CharaSele_Player::CH_STT_X_1P = 402;
	const float CharaSele_Player::CH_STT_X_2P = 405;
	const float CharaSele_Player::CH_STT_CHARA_Y = 8;
	const float CharaSele_Player::CH_STT_STAGE_Y = 370;
	const float CharaSele_Player::CH_STT_BGM_Y = 552;
	const float CharaSele_Player::CH_STT_OK_Y = 2000;	//画面外

	const uint32 CharaSele_Player::PLAYER = 0;
	const uint32 CharaSele_Player::CPU = 1;



	CharaSele_Player::CharaSele_Player ()
	{
		//キャラ立絵
		m_chara_stand = std::make_shared < GameGraphic > ();
		m_chara_stand->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka.png" );
		m_chara_stand->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_stand->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae.png" );
		m_chara_stand->AddTexture_FromArchive ( U"CharaSele\\Stand_Retsudou.png" );
		AddpTask ( m_chara_stand );
		GRPLST_INSERT ( m_chara_stand );

		//キャラ立絵(明度)
		m_chara_stand_light = std::make_shared < GameGraphic > ();
		m_chara_stand_light->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka_light.png" );
		m_chara_stand_light->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_stand_light->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae_light.png" );
		m_chara_stand_light->AddTexture_FromArchive ( U"CharaSele\\Stand_Retsudou_light.png" );
		AddpTask ( m_chara_stand_light );
		GRPLST_INSERT ( m_chara_stand_light );
		m_chara_stand_light->SetValid ( F );

		//キャラ名前
		m_chara_name = std::make_shared < GameGraphic > ();
		m_chara_name->AddTexture_FromArchive ( U"CharaSele\\Name_Ouka.png" );
		m_chara_name->AddTexture_FromArchive ( U"hit\\0.png" );	//Padding
		m_chara_name->AddTexture_FromArchive ( U"CharaSele\\Name_Sae.png" );
		m_chara_name->AddTexture_FromArchive ( U"CharaSele\\Name_Retsudou.png" );
		AddpTask ( m_chara_name );
		GRPLST_INSERT ( m_chara_name );

		//カーソル
		m_cursor = std::make_shared < GrpBlink > ();
		m_cursor->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Cursor_1p.png" );
		m_cursor->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Cursor_2p.png" );
		m_cursor->SetTimer ( 15 );
		m_cursor->SetZ ( Z_SYS );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		//状態表示
		m_state_Disp = std::make_shared < GrpBlink > ();
		m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\1P_State.png" );
		m_state_Disp->AddTexture_FromArchive ( U"CharaSele\\2P_State.png" );
		m_state_Disp->SetBlinkTime ( 20 );
		m_state_Disp->SetHalf ( T );
		m_state_Disp->SetZ ( Z_MENU );
		AddpTask ( m_state_Disp );
		GRPLST_INSERT ( m_state_Disp );

		//-----------------------------------------------------------------------
		//入力者 
		m_grp_Cst_InputPlayerCOM = std::make_shared < GameGraphic > ();
		m_grp_Cst_InputPlayerCOM->AddTexture_FromArchive ( U"INPUT_PLAYER.png" );
		m_grp_Cst_InputPlayerCOM->AddTexture_FromArchive ( U"INPUT_CPU.png" );
		m_grp_Cst_InputPlayerCOM->SetZ ( Z_SYS );
		AddpTask ( m_grp_Cst_InputPlayerCOM );
		GRPLST_INSERT ( m_grp_Cst_InputPlayerCOM );

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
			m_cursor->SetPos ( VEC2 ( m_pos [ CHSLID_00 ].x, m_pos [ CHSLID_00 ].y ) );
			m_cursor->SetIndexTexture ( 0 );
			m_state_Disp->SetIndexTexture ( 0 );
			m_state_Disp->SetPos ( CH_STT_X_1P, CH_STT_CHARA_Y );
			m_grp_Cst_InputPlayerCOM->SetPos ( 300, 5 );
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
			m_cursor->SetPos ( VEC2 ( m_pos [ CHSLID_02 ].x, m_pos [ CHSLID_02 ].y ) );
			m_cursor->SetIndexTexture ( 1 );
			m_state_Disp->SetIndexTexture ( 1 );
			m_state_Disp->SetPos ( CH_STT_X_2P, CH_STT_CHARA_Y );
			m_grp_Cst_InputPlayerCOM->SetPos ( 1280 - 64 - 300, 5 );
		}

	}

	void CharaSele_Player::ParamInit ( P_Param p )
	{
		m_pParam = p;
//		p->GetCharaName ( m_player_id );
		MUTCH_MODE mutch = m_pParam->GetMutchMode ();

		if ( PLAYER_ID_1 == m_player_id )
		{
			switch ( mutch )
			{
			case MUTCH_MODE::MODE_PLAYER_CPU :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( PLAYER );
				m_Input_1P_Only = T;
				break;
			case MUTCH_MODE::MODE_PLAYER_PLAYER :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( PLAYER );
				m_Input_1P_Only = F;
				break;
			case MUTCH_MODE::MODE_CPU_CPU :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( CPU );
				m_Input_1P_Only = T;
				break;
			}
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			switch ( mutch )
			{
			case MUTCH_MODE::MODE_PLAYER_CPU :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( CPU );
				m_Input_1P_Only = T;
				break;
			case MUTCH_MODE::MODE_PLAYER_PLAYER :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( PLAYER );
				m_Input_1P_Only = F;
				break;
			case MUTCH_MODE::MODE_CPU_CPU :
				m_grp_Cst_InputPlayerCOM->SetIndexTexture ( CPU );
				m_Input_1P_Only = T;	//CPUvsCPUも１Pが両者を選択
				break;
			}
		}

		//トレーニングモードはPvPだがキャラセレは1Pのみ
		GAME_MODE game_mode = p->GetGameMode ();
		if ( MODE_TRAINING == game_mode )
		{
			m_Input_1P_Only = T;
		}
	}

	void CharaSele_Player::Move ()
	{
		//状態による分岐
		switch ( m_state )
		{
		case STT_CHARA: Move_Chara	(); break;
		case STT_COLOR: Move_Color	(); break;
		case STT_STAGE: Move_Stage	(); break;
		case STT_BGM:	Move_bgm	(); break;
		case STT_OK:	Move_OK		(); break;
		default: break;
		};

#if 0

		//入力
		if ( m_decided )	//決定済みならば
		{
			Input_Decided ();	//キャンセルのみ
		}
		else
		{
			Input ();	//移動と決定
		}

#endif // 0

		TASK_VEC::Move ();
	}

	//-------------------------------------------
	void CharaSele_Player::Move_Chara ()
	{
		Input_Chara ();	//移動と決定

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

		TASK_VEC::Move ();
	}

	void CharaSele_Player::Move_Color ()
	{
		TASK_VEC::Move ();
	}

	void CharaSele_Player::Move_Stage ()
	{
		//キャラ決定後
		if ( ++ m_wait > 10 )
		{
			//明度を戻す
			m_chara_stand->SetValid ( T );
			m_chara_stand_light->SetValid ( F );
			m_wait = 0;
		}

		Input_Stage ();

		TASK_VEC::Move ();
	}

	void CharaSele_Player::Move_bgm ()
	{
		Input_BGM ();
		TASK_VEC::Move ();
	}

	void CharaSele_Player::Move_OK ()
	{
		Input_OK ();	//キャンセルのみ
		TASK_VEC::Move ();
	}


	//-------------------------------------------
	CHARA_NAME CharaSele_Player::GetName () const
	{
		return m_pos[m_chsl_id].Name;
	}


	//キャラ名から選択する
	void CharaSele_Player::AssignName ( CHARA_NAME name )
	{
		switch ( name )
		{
		case CHARA_OUKA:		 m_chsl_id = CHSLID_00; break;
		case CHARA_SAE:			 m_chsl_id = CHSLID_02; break;
		case CHARA_RETSUDOU:	 m_chsl_id = CHSLID_03; break;
		}

		//選択キャラ表示
		switch ( m_chsl_id )
		{
		case CHSLID_00: SetCharaStand ( CHSLID_00 ); break;
		case CHSLID_01: HiddenCharaStand ();break;
		case CHSLID_02: SetCharaStand ( CHSLID_02 ); break;
		case CHSLID_03: SetCharaStand ( CHSLID_03 ); break;
		case CHSLID_04: HiddenCharaStand ();break;
		case CHSLID_05: HiddenCharaStand ();break;
		case CHSLID_06: HiddenCharaStand ();break;
		case CHSLID_07: HiddenCharaStand ();break;
		case CHSLID_08: HiddenCharaStand ();break;
		case CHSLID_09: HiddenCharaStand ();break;
		default: break;
		}

		//カーソル位置も更新
		m_cursor->SetPos ( VEC2 ( m_pos [ m_chsl_id ].x, m_pos [ m_chsl_id ].y ) );
	}



	void CharaSele_Player::SetCursorUp ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		CHARA_SELE_ID next_id = m_pos [ id ].UP;
		pCrs->SetPos ( VEC2 ( m_pos [ next_id ].x, m_pos [ next_id ].y ) );
		id = next_id;
		Select ();
	}
	void CharaSele_Player::SetCursorDown ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		CHARA_SELE_ID next_id  = m_pos [ id ].DOWN;
		pCrs->SetPos ( VEC2 ( m_pos [ next_id ].x, m_pos [ next_id ].y ) );
		id = next_id;
		Select ();
	}
	void CharaSele_Player::SetCursorLeft ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		CHARA_SELE_ID next_id  = m_pos [ id ].LEFT;
		pCrs->SetPos ( VEC2 ( m_pos [ next_id ].x, m_pos [ next_id ].y ) );
		id = next_id;
		Select ();
	}
	void CharaSele_Player::SetCursorRight ( P_GrpBlink pCrs, CHARA_SELE_ID & id )
	{
		CHARA_SELE_ID next_id  = m_pos [ id ].RIGHT;
		pCrs->SetPos ( VEC2 ( m_pos [ next_id ].x, m_pos [ next_id ].y ) );
		id = next_id;
		Select ();
	}


	//-------------------------------------------------------------------
	//入力
	void CharaSele_Player::Input_Chara ()
	{
		//条件チェック
		if ( IsNotSelect () ) { return; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき1P側入力で操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;

			//ボタン１でキャンセル
			if ( CFG_PUSH_KEY_PL ( id, PLY_BTN1 ) )
			{
				m_back_to_1p = T;
			}
		}


		//移動
		if ( CFG_PUSH_KEY_PL ( id, PLY_UP) ) { SetCursorUp ( m_cursor, m_chsl_id ); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_DOWN ) ) { SetCursorDown ( m_cursor, m_chsl_id ); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_LEFT ) ) { SetCursorLeft ( m_cursor, m_chsl_id ); }
		if ( CFG_PUSH_KEY_PL ( id, PLY_RIGHT ) ) { SetCursorRight ( m_cursor, m_chsl_id ); }

		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN0 ) )
		{
			Decide ();
		}
	}

	void CharaSele_Player::Input_Color ()
	{
		//条件チェック
		if ( IsNotSelect () ) { return; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき1P側入力で操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}


		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN0 ) )
		{
			//ステートを変更
			m_state = STT_STAGE;
			m_state_Disp->SetPosY ( CH_STT_STAGE_Y );
		}

		//ボタン１でキャンセル
		if ( CFG_PUSH_KEY_PL ( m_player_id, PLY_BTN1 ) )
		{
			Cancel ();
		}
	}


	void CharaSele_Player::Input_Stage ()
	{
		//条件チェック
		if ( IsNotSelect () ) { return; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき1P側入力で操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}


		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN0 ) )
		{
			//ステートを変更
			m_state = STT_BGM;
			m_state_Disp->SetPosY ( CH_STT_BGM_Y );
		}

		//ボタン１でキャンセル
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN1 ) )
		{
			//ステートを変更
			m_state = STT_CHARA;
			m_state_Disp->SetPosY ( CH_STT_CHARA_Y );
			SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
		}
	}

	void CharaSele_Player::Input_BGM ()
	{
		//条件チェック
		if ( IsNotSelect () ) { return; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき1P側入力で操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}


		//ボタン0で決定
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN0 ) )
		{
			//ステートを変更
			m_state = STT_OK;
			m_state_Disp->SetPosY ( CH_STT_OK_Y );

			if ( m_Input_1P_Only && Is1P() )
			{
				m_decide_1P = T;	//1P側選択終了、2P側へ移行
			}
		}

		//ボタン１でキャンセル
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN1 ) )
		{
			//ステートを変更
			m_state = STT_STAGE;
			m_state_Disp->SetPosY ( CH_STT_STAGE_Y );
			SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

			SND_STOP_ALL_BGM();
			SND_PLAY_LOOP_BGM ( BGM_CharaSele );	//初期BGMはキャラセレBGM
		}
	}


	void CharaSele_Player::Input_OK ()
	{
		//条件チェック
		if ( IsNotSelect () ) { return; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき1P側入力で操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}

		//1Pが2P側を操作しているとき何もしない
		if ( m_Input_1P_Only && m_decide_1P ) { return; }

		//ボタン１でキャンセル
		if ( CFG_PUSH_KEY_PL ( id, PLY_BTN1 ) )
		{
			//ステートを変更
			m_state = STT_BGM;
			m_state_Disp->SetPosY ( CH_STT_BGM_Y );
			SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
		}
	}


	//2Pからキャンセルして1PのBGMに戻る
	void CharaSele_Player::BackTo1pBGM ()
	{
		//ステートを変更
		m_state = STT_BGM;
		m_state_Disp->SetPosY ( CH_STT_BGM_Y );
		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );
	}



	//キャンセル
	void CharaSele_Player::Cancel ()
	{
		m_decided = F;
		m_chara_stand->SetValid ( T );
		m_chara_stand_light->SetValid ( F );
		m_cursor->Start ();

		//ステートを変更
		m_state = STT_CHARA;
		m_state_Disp->SetPosY ( CH_STT_CHARA_Y );

		SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

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

		//選択キャラ表示
		switch ( m_chsl_id )
		{
		case CHSLID_00: SetCharaStand ( CHSLID_00 ); break;
		case CHSLID_01: HiddenCharaStand ();break;
		case CHSLID_02: SetCharaStand ( CHSLID_02 ); break;
		case CHSLID_03: SetCharaStand ( CHSLID_03 ); break;
		case CHSLID_04: HiddenCharaStand ();break;
		case CHSLID_05: HiddenCharaStand ();break;
		case CHSLID_06: HiddenCharaStand ();break;
		case CHSLID_07: HiddenCharaStand ();break;
		case CHSLID_08: HiddenCharaStand ();break;
		case CHSLID_09: HiddenCharaStand ();break;
		default: break;
		}

		SND_PLAY_ONESHOT_SE ( SE_select_move );
	}

	//決定時
	void CharaSele_Player::Decide ()
	{
		//選択可能かどうか
		if ( ! CanSelect () )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_Lock );
			return;
		}

		m_decided = T; 
		m_cursor->Stop ();
		m_chara_stand->SetValid ( F );
		m_chara_stand_light->SetValid ( T );

		//ステートを変更
		m_state = STT_STAGE;
		m_state_Disp->SetPosY ( CH_STT_STAGE_Y );

		SND_PLAY_ONESHOT_SE ( SE_select_decide );

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
		case CHSLID_03: return T;
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
		m_chara_stand_light->SetValid ( F );
		m_chara_stand_light->SetIndexTexture ( id ); 
		m_chara_name->SetValid ( T );
		m_chara_name->SetIndexTexture ( id );
	}


	void CharaSele_Player::HiddenCharaStand ()
	{
		m_chara_stand->SetValid ( F ); 
		m_chara_name->SetValid ( F );
	}



	//1Pが両者選択のとき2Pなら操作しない
	//ただし、1Pが操作終了後は1Pが操作する
	bool CharaSele_Player::IsNotSelect () const
	{
		//ただし、1Pが操作終了後は1Pが操作する
		if ( m_Input_1P_Only && m_decide_1P ) { return F; }

		//1Pが両者選択のとき2Pなら操作しない
		return Is2P () && m_Input_1P_Only;
	}




	//外部から見るキー操作
	bool CharaSele_Player::PUSH_KEY_LEFT () const
	{
		//条件チェック
		if ( IsNotSelect () ) { return F; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき2P側を操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}

		//該当IDが左を入力
		return	 CFG_PUSH_KEY_PL ( id, PLY_LEFT );
	}

	bool CharaSele_Player::PUSH_KEY_RIHGT () const
	{
		//条件チェック
		if ( IsNotSelect () ) { return F; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき2P側を操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}

		//該当IDが右を入力
		return	 CFG_PUSH_KEY_PL ( id, PLY_RIGHT );
	}

	bool CharaSele_Player::PUSH_KEY_DECIDE () const
	{
		//条件チェック
		if ( IsNotSelect () ) { return F; }

		//操作側ID
		PLAYER_ID id = m_player_id; //初期値

		//1Pのみ操作で1P決定済みのとき2P側を操作
		if ( m_Input_1P_Only && m_decide_1P )
		{
			id = PLAYER_ID_1;
		}

		//該当IDがボタン０を入力
		return	 CFG_PUSH_KEY_PL ( id, PLY_BTN0 );
	}


}	//namespace GAME

