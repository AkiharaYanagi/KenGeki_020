//=================================================================================================
//
//	CharaSele ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"
#include "../GameMain/SoundConst.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region CONST

	//キャラセレ
	const float CharaSele::TXT_CHSL_X = 640 - 270 / 2;
	const float CharaSele::TXT_CHSL_Y = 24;

	//キャラ別
	const float CharaSele::CH_INDEX_X_1P = 0    + 100;
	const float CharaSele::CH_INDEX_X_2P = 1280 - 100 - 194;
	const float CharaSele::CH_INDEX_Y = 5;

	const float CharaSele::CH_BAR_X_1P = 405;
	const float CharaSele::CH_BAR_X_2P = 405;
	const float CharaSele::CH_BAR_Y = 0;

	//ステージセレクト
	const float CharaSele::STG_BG_X = 0;
	const float CharaSele::STG_BG_Y = 385;
	const float CharaSele::TXT_STSL_X = 640 - 260 / 2;
	const float CharaSele::TXT_STSL_Y = 390;
	const float CharaSele::STG_X = 640 - 256 / 2;
	const float CharaSele::STG_Y = 420;
	const float CharaSele::STG_TRI_X = (1280 - 335) * 0.5f;
	const float CharaSele::STG_TRI_Y = STG_Y + 50;

	//BGMセレクト
	const float CharaSele::BGM_SCROLL_X = 1280;
	const float CharaSele::BGM_SCROLL_Y = 570;
	const float CharaSele::TXT_BGM_X  = 640 - 184 / 2;
	const float CharaSele::TXT_BGM_Y  = 572;
	const float CharaSele::BGM_X = 640 - 225;
	const float CharaSele::BGM_Y = 605;
	const float CharaSele::BGM_TRI_X = (1280 - 450) * 0.5f;
	const float CharaSele::BGM_TRI_Y = BGM_Y + 4;

	//操作説明
	const float CharaSele::INST_X = 0;
	const float CharaSele::INST_Y = 960 - 27;

#pragma endregion


	CharaSele::CharaSele ()
	{
		//BG(全体)
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"CharaSele\\CharaSele_BG.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		//Scroll(全体)
		m_scroll = std::make_shared < GameGraphic > ();
		m_scroll->SetShader ( T );
		m_scroll->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll.png" );
		m_scroll->SetPos ( 0, 0 );
		m_scroll->SetZ ( Z_BG );
		AddpTask ( m_scroll );
		GRPLST_INSERT ( m_scroll );



		//CharaFace
		m_charaFace = std::make_shared < GameGraphic > ();
		m_charaFace->AddTexture_FromArchive ( U"CharaSele\\CharaFace.png" );
		m_charaFace->SetPos ( (1280 - 455) / 2, 70 );
		m_charaFace->SetZ ( Z_EFF );
		AddpTask ( m_charaFace );
		GRPLST_INSERT ( m_charaFace );



		//プレイヤ別の位置など
		m_chsl_pl_1p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_1p->PlayerInit ( PLAYER_ID_1 );
		AddpTask ( m_chsl_pl_1p );

		m_chsl_pl_2p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_2p->PlayerInit ( PLAYER_ID_2 );
		AddpTask ( m_chsl_pl_2p );


		//現在状態
		m_index_1p = std::make_shared < GameGraphic > ();
		m_index_1p->AddTexture_FromArchive ( U"CharaSele\\1P_Index.png" );
		m_index_1p->SetPos ( CH_INDEX_X_1P, CH_INDEX_Y );
		AddpTask ( m_index_1p );
		GRPLST_INSERT ( m_index_1p );

		m_index_2p = std::make_shared < GameGraphic > ();
		m_index_2p->AddTexture_FromArchive ( U"CharaSele\\2P_Index.png" );
		m_index_2p->SetPos ( CH_INDEX_X_2P, CH_INDEX_Y );
		AddpTask ( m_index_2p );
		GRPLST_INSERT ( m_index_2p );


#if 0

		m_state_1p = std::make_shared < GrpBlink > ();
		m_state_1p->AddTexture_FromArchive ( U"CharaSele\\1P_State.png" );
		m_state_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
		m_state_1p->SetBlinkTime ( 20 );
		m_state_1p->SetHalf ( T );
		AddpTask ( m_state_1p );
		GRPLST_INSERT ( m_state_1p );

		m_state_2p = std::make_shared < GrpBlink > ();
		m_state_2p->AddTexture_FromArchive ( U"CharaSele\\2P_State.png" );
		m_state_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
		m_state_2p->SetBlinkTime ( 20 );
		m_state_2p->SetHalf ( T );
		AddpTask ( m_state_2p );
		GRPLST_INSERT ( m_state_2p );

#endif // 0



		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		m_fade_toTitle->SetAfterClear ( F );
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		m_fade_toFighting->SetAfterClear ( F );
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );


		//-----------------------------------------------------------------------
		//文字表示
		m_txt_CharacterSelect = std::make_shared < GrpBlink > ();
		m_txt_CharacterSelect->AddTexture_FromArchive ( U"CharaSele\\Text_CHARACTER_SELECT.png" );
		m_txt_CharacterSelect->SetPos ( VEC2 ( TXT_CHSL_X, TXT_CHSL_Y ) );
		m_txt_CharacterSelect->SetZ ( Z_SYS );
//		m_txt_CharacterSelect->Start ();
		m_txt_CharacterSelect->SetHalf ( T );
		AddpTask ( m_txt_CharacterSelect );
		GRPLST_INSERT ( m_txt_CharacterSelect );


		//-----------------------------------------------------------------------
		//ステージセレクト
		
		//Scroll Stage
		m_scroll_Stage = std::make_shared < GameGraphic > ();
		m_scroll_Stage->SetShader ( T );
		m_scroll_Stage->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll_Stage.png" );
		m_scroll_Stage->SetPos ( STG_BG_X, STG_BG_Y );
		m_scroll_Stage->SetScaling ( VEC2 ( 1.f, 0.875f ) );
//		m_scroll_Stage->SetScaling ( VEC2 ( 1.f, 1.f ) );
		m_scroll_Stage->SetZ ( Z_BG );
		AddpTask ( m_scroll_Stage );
		GRPLST_INSERT ( m_scroll_Stage );

		m_txt_StageSelect = std::make_shared < GrpBlink > ();
		m_txt_StageSelect->AddTexture_FromArchive ( U"CharaSele\\Text_STAGE_SELECT.png" );
		m_txt_StageSelect->SetPos ( VEC2 ( TXT_STSL_X, TXT_STSL_Y ) );
		m_txt_StageSelect->SetZ ( Z_SYS );
		m_txt_StageSelect->Stop ();
		m_txt_StageSelect->SetHalf ( T );
		AddpTask ( m_txt_StageSelect );
		GRPLST_INSERT ( m_txt_StageSelect );

		m_stageSelect = std::make_shared < GameGraphic > ();
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Noon.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Evening.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Night.png" );
		m_stageSelect->SetPos ( VEC2 ( STG_X, STG_Y ) );
		m_stageSelect->SetZ ( Z_EFF );
		AddpTask ( m_stageSelect );
		GRPLST_INSERT ( m_stageSelect );

		m_stageSelectTri = std::make_shared < GrpBlink > ();
		m_stageSelectTri->AddTexture_FromArchive ( U"CharaSele\\SelectTriangleStage.png" );
		m_stageSelectTri->SetPos ( VEC2 ( STG_TRI_X, STG_TRI_Y ) );
		m_stageSelectTri->SetZ ( Z_EFF );
		m_stageSelectTri->SetHalf ( T );
		AddpTask ( m_stageSelectTri );
		GRPLST_INSERT ( m_stageSelectTri );


		//-----------------------------------------------------------------------
		//BGM

		//Scroll bgm
		m_scroll_bgm = std::make_shared < GameGraphic > ();
		m_scroll_bgm->SetShader ( T );
		m_scroll_bgm->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll_Stage.png" );
		m_scroll_bgm->SetPos ( BGM_SCROLL_X, BGM_SCROLL_Y );
		m_scroll_bgm->SetScaling ( VEC2 ( -1.f, 0.3f ) );
//		m_scroll_bgm->SetScaling ( VEC2 ( -1.f, 1.f ) );
		m_scroll_bgm->SetZ ( Z_BG );
		AddpTask ( m_scroll_bgm );
		GRPLST_INSERT ( m_scroll_bgm );

		m_txt_BGMSelect = std::make_shared < GrpBlink > ();
		m_txt_BGMSelect->AddTexture_FromArchive ( U"CharaSele\\Text_BGM_SELECT.png" );
		m_txt_BGMSelect->SetPos ( VEC2 ( TXT_BGM_X, TXT_BGM_Y ) );
		m_txt_BGMSelect->SetZ ( Z_SYS );
		m_txt_BGMSelect->Stop ();
		m_txt_BGMSelect->SetHalf ( T );
		AddpTask ( m_txt_BGMSelect );
		GRPLST_INSERT ( m_txt_BGMSelect );

		m_bgmSelect = std::make_shared < GameGraphic > ();
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_GABADARUGA.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_HIYODORI_OUKA.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_TOMOE_SAE.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_REKKA_RETSUDOU.png" );
		m_bgmSelect->SetPos ( VEC2 ( BGM_X, BGM_Y ) );
		m_bgmSelect->SetZ ( Z_EFF );
		AddpTask ( m_bgmSelect );
		GRPLST_INSERT ( m_bgmSelect );

		m_bgmSelectTri = std::make_shared < GrpBlink > ();
		m_bgmSelectTri->AddTexture_FromArchive ( U"CharaSele\\SelectTriangleBGM.png" );
		m_bgmSelectTri->SetPos ( VEC2 ( BGM_TRI_X, BGM_TRI_Y ) );
		m_bgmSelectTri->SetZ ( Z_EFF );
		m_bgmSelectTri->SetHalf ( T );
		AddpTask ( m_bgmSelectTri );
		GRPLST_INSERT ( m_bgmSelectTri );

		m_scrlbgm_x = BGM_SCROLL_X;

#if 0
		ma_bgm.push_back ( BGM_GABA );
		ma_bgm.push_back ( BGM_OUKA );
		ma_bgm.push_back ( BGM_SAE );
		ma_bgm.push_back ( BGM_RETSU );
#endif // 0


		//-----------------------------------------------------------------------
		//操作説明
		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"CharaSele\\Inst_CharaSele.png" );
		m_inst->SetPos ( VEC2 ( INST_X, INST_Y ) );
		m_inst->SetZ ( Z_SYS );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );


	}

	CharaSele::~CharaSele ()
	{
	}


	void CharaSele::ParamInit ()
	{
		P_Param p = GetpParam ();
		m_chsl_pl_1p->ParamInit ( p );
		m_chsl_pl_2p->ParamInit ( p );

		//パラメータからキャラ選択の初期位置を設定する
		CHARA_NAME charaName1p = p->GetCharaName1p ();
		m_chsl_pl_1p->AssignName ( charaName1p );
		CHARA_NAME charaName2p = p->GetCharaName2p ();
		m_chsl_pl_2p->AssignName ( charaName2p );

		//ステージ
		STAGE_NAME stageName = p->GetStageName ();
		AssignStage ( stageName );

		//BGM
		m_bgm_id = p->Get_BGM_ID ();

		//読み込んだBGM_IDの表示だけ変更する
		m_bgmSelect->SetIndexTexture ( m_bgm_id );
	}


	void CharaSele::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		//SOUND
		SND_STOP_ALL_BGM();
		SND_PLAY_LOOP_BGM ( BGM_CharaSele );	//初期BGMはキャラセレBGM

		Scene::Load ();
	}

	P_GameScene CharaSele::Transit ()
	{
		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM();
			Scene::Transit_Title ();
		}

		//戦闘に移行
		if ( m_fade_toFighting->IsLast () )
		{
			Save ();
			m_fade_toFighting->ShiftTargetColor ();

			SND_STOP_ALL_BGM ();

			//通常戦闘かトレーニングの分岐
			P_Param pPrm = Scene::GetpParam ();
			if ( MODE_MAIN == pPrm->GetGameMode () )
			{
				Scene::Transit_Fighting ();
			}
			else if ( MODE_TRAINING == pPrm->GetGameMode () )
			{
				Scene::Transit_Training ();
			}
		}

#if 0

		//フェード待機後、遷移開始
		if ( m_fade_toFighting->IsLast () )
		{
			++ m_plus_wait;
		}

		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > 15 )
			{

				m_plus_wait = 0;
			}
			++ m_plus_wait;
		}

#endif // 0

		return Scene::Transit (); 
	}

	//キャラ選択、ステージ選択をパラメータに記録
	void CharaSele::Save ()
	{
		//パラメータに記録し、次シーン以降で用いる
		P_Param pPrm = Scene::GetpParam ();
		pPrm->SetCharaName1p ( m_chsl_pl_1p->GetName() );
		pPrm->SetCharaName2p ( m_chsl_pl_2p->GetName() );
		pPrm->SetStageName ( GetStageName () );
		pPrm->Set_BGM_ID ( m_bgm_id );

		//設定ファイルに書出
		pPrm->GetGameSetting().Save ();
	}


	void CharaSele::Move ()
	{
		//----------------------------------------------------------
		// 表示類
		
		//背景スクロール
		m_scrl_y -= 20;
		if ( m_scrl_y < - 960 ) { m_scrl_y = 0; }
		m_scroll->SetPos ( 0, m_scrl_y );

		m_scrlStg_x -= 20;
		if ( m_scrlStg_x < - 1280 ) { m_scrlStg_x = 0; }
		m_scroll_Stage->SetPos ( m_scrlStg_x, STG_BG_Y );

		m_scrlbgm_x += 20;
		if ( 1280 + 1280 < m_scrlbgm_x ) { m_scrlbgm_x = 1280; }
		m_scroll_bgm->SetPos ( m_scrlbgm_x, BGM_SCROLL_Y );


		//選択状態
		CharaSele_Player::CHST_PL_State stt1p = m_chsl_pl_1p->GetState ();
		CharaSele_Player::CHST_PL_State stt2p = m_chsl_pl_2p->GetState ();

		bool b1Ch = stt1p == CharaSele_Player::STT_CHARA;
		bool b2Ch = stt2p == CharaSele_Player::STT_CHARA;

		//キャラセレクト
		if ( b1Ch || b2Ch )
		{
			//点滅
			m_txt_CharacterSelect->Start ();
		}
		else
		{
			m_txt_CharacterSelect->Stop ();
		}

		bool b1Stg = stt1p == CharaSele_Player::STT_STAGE;
		bool b2Stg = stt2p == CharaSele_Player::STT_STAGE;

		//ステージセレクト
		if ( b1Stg || b2Stg )
		{
			//点滅
			m_txt_StageSelect->Start ();
			m_stageSelectTri->Start ();
		}
		else
		{
			m_txt_StageSelect->Stop ();
			m_stageSelectTri->Stop ();
		}


		bool b1BGM = stt1p == CharaSele_Player::STT_BGM;
		bool b2BGM = stt2p == CharaSele_Player::STT_BGM;

		//BGMセレクト
		if ( b1BGM || b2BGM )
		{
			//点滅
			m_txt_BGMSelect->Start ();
			m_bgmSelectTri->Start ();
		}
		else
		{
			m_txt_BGMSelect->Stop ();
			m_bgmSelectTri->Stop ();
		}


		//----------------------------------------------------------
		//フェードアウト中の待機と遷移
		if ( m_fade_toTitle->IsActive() )
		{
			Scene::Move (); 
			return;
		}

		//戦闘に移行
		if ( m_fade_toFighting->IsActive () )
		{
			Scene::Move (); 
			return;
		}

		//----------------------------------------------------------
		//入力
		Input ();


		//両者すべてを決定したらFtgMainに移行
		bool bOK1 = stt1p == CharaSele_Player::STT_OK;
		bool bOK2 = stt2p == CharaSele_Player::STT_OK;

		if ( bOK1 && bOK2 )
		{
			if ( ! m_fade_toFighting->IsActive () )
			{
				//フェード開始
				m_fade_toFighting->StartBlackOut ( 16 );
			}
		}

		Scene::Move (); 
	}


	void CharaSele::Input ()
	{
		//BackSpaceでタイトルに戻る (ESCは直接終了)
		//コントローラ(7:リセットボタン)でも戻る
		if ( ! m_fade_toTitle->IsActive () )
		{
			bool bBackSpace = WND_UTL::AscKey ( VK_BACK );
			bool bCtrlReset = CFG_PUSH_KEY_12 ( PLAYER_INPUT::PLY_BTN7 );
			if ( bBackSpace || bCtrlReset )
			{
				SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

				//フェード開始
				m_fade_toTitle->StartBlackOut ( 8 );
			}
		}


		//選択状態
		CharaSele_Player::CHST_PL_State stt1p = m_chsl_pl_1p->GetState ();
		CharaSele_Player::CHST_PL_State stt2p = m_chsl_pl_2p->GetState ();

		//ステージセレクト
		if ( stt1p == CharaSele_Player::STT_STAGE )
		{
			if ( m_chsl_pl_1p->PUSH_KEY_LEFT ()   ) { StagePrev (); }
			if ( m_chsl_pl_1p->PUSH_KEY_RIHGT ()  ) { StageNext (); }
			if ( m_chsl_pl_1p->PUSH_KEY_DECIDE () ) { StageDecide (); }
		}
		if ( stt2p == CharaSele_Player::STT_STAGE )
		{
			if ( m_chsl_pl_2p->PUSH_KEY_LEFT ()   ) { StagePrev (); }
			if ( m_chsl_pl_2p->PUSH_KEY_RIHGT ()  ) { StageNext (); }
			if ( m_chsl_pl_2p->PUSH_KEY_DECIDE () ) { StageDecide (); }
		}

		//BGMセレクト
		if ( stt1p == CharaSele_Player::STT_BGM )
		{
			if ( m_chsl_pl_1p->PUSH_KEY_LEFT ()   ) { BGM_Prev (); }
			if ( m_chsl_pl_1p->PUSH_KEY_RIHGT ()  ) { BGM_Next (); }
			if ( m_chsl_pl_1p->PUSH_KEY_DECIDE () ) { BGM_Decide (); }
		}
		if ( stt2p == CharaSele_Player::STT_BGM )
		{
			if ( m_chsl_pl_2p->PUSH_KEY_LEFT ()   ) { BGM_Prev (); }
			if ( m_chsl_pl_2p->PUSH_KEY_RIHGT ()  ) { BGM_Next (); }
			if ( m_chsl_pl_2p->PUSH_KEY_DECIDE () ) { BGM_Decide (); }
		}


		//----------------------
		//1Pのみ操作時
		 
		//1Pの終了チェックを2P側に知らせる
		m_chsl_pl_2p->SetDecide1P ( m_chsl_pl_1p->GetDecide1P () );

		//2P側をキャンセルして1P側に戻る
		if ( m_chsl_pl_2p->GetBackTo1P () )
		{
			m_chsl_pl_1p-> BackTo1pBGM ();
			m_chsl_pl_2p->SetBackTo1P ( F );

			//決定済みを解除
			m_chsl_pl_1p->SetDecide1P ( F );
			m_chsl_pl_2p->SetDecide1P ( F );
		}
	}


	//-------------------------------------------------
	void CharaSele::StagePrev ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_stageSelect->PrevIndexTexture ();
	}

	void CharaSele::StageNext ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_stageSelect->NextIndexTexture ();
	}

	void CharaSele::StageDecide ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_decide );
		m_stageDecide = T;

		//BGM選択に以降するときに初期値で変更する
		SND_STOP_ALL_BGM();
		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ m_bgm_id ] );

	}


	//-------------------------------------------------
	STAGE_NAME CharaSele::GetStageName ()
	{
		STAGE_NAME ret = STAGE_YUUHINO_HARA;

		switch ( m_stageSelect->Getpap_ob()->at ( 0 )->GetIndexTexture () )
		{
		case 0: ret = STAGE_ASAHINO_HARA; break;
		case 1: ret = STAGE_YUUHINO_HARA; break;
		case 2: ret = STAGE_YORUNO_HARA; break;
		}

		return ret;
	}

	void CharaSele::AssignStage ( STAGE_NAME name )
	{
		m_stageSelect->SetIndexTexture ( (uint32) name );
	}

	//-------------------------------------------------
	void CharaSele::BGM_Prev ()
	{
		switch ( m_bgm_id )
		{
		case BGM_ID_GABA:	m_bgm_id = BGM_ID_OUKA;		 break;
		case BGM_ID_OUKA:	m_bgm_id = BGM_ID_SAE;		 break;
		case BGM_ID_SAE:	m_bgm_id = BGM_ID_RETSU;	 break;
		case BGM_ID_RETSU:	m_bgm_id = BGM_ID_GABA;		 break;
		}

		Set_BGM_ID ( m_bgm_id );
	}

	void CharaSele::BGM_Next ()
	{
		switch ( m_bgm_id )
		{
		case BGM_ID_GABA:	m_bgm_id = BGM_ID_RETSU;	 break;
		case BGM_ID_OUKA:	m_bgm_id = BGM_ID_GABA;		 break;
		case BGM_ID_SAE:	m_bgm_id = BGM_ID_OUKA;		 break;
		case BGM_ID_RETSU:	m_bgm_id = BGM_ID_SAE;		 break;
		}

		Set_BGM_ID ( m_bgm_id );
	}

	void CharaSele::Set_BGM_ID ( BGM_ID id )
	{
		m_bgm_id = id;
		m_bgmSelect->SetIndexTexture ( m_bgm_id );
		SND_STOP_ALL_BGM();
//		SND_PLAY_LOOP_BGM ( ma_bgm [ id ] );
		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ id ] );
	}

	void CharaSele::BGM_Decide ()
	{
		GetpParam()->Set_BGM_ID ( m_bgm_id );
		SND_PLAY_ONESHOT_SE ( SE_select_decide );
	}



}	//namespace GAME

