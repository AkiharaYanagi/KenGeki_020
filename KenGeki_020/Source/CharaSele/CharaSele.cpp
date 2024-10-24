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
	const float CharaSele::TXT_CHSL_X = -2 + 640 - 286 / 2;
	const float CharaSele::TXT_CHSL_Y = 5;

	//キャラ別
	const float CharaSele::CH_INDEX_X_1P = 0    + 100;
	const float CharaSele::CH_INDEX_X_2P = 1280 - 100 - 194;
	const float CharaSele::CH_INDEX_Y = 5;

	const float CharaSele::CH_STT_X_1P = 410;
	const float CharaSele::CH_STT_X_2P = 800;
	const float CharaSele::CH_STT_Y = 5;

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
	const float CharaSele::BGM_Y = 602;
	const float CharaSele::BGM_TRI_X = (1280 - 335) * 0.5f;
	const float CharaSele::BGM_TRI_Y = BGM_Y + 50;

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



		m_state_1p = std::make_shared < GrpBlink > ();
		m_state_1p->AddTexture_FromArchive ( U"CharaSele\\1P.png" );
		m_state_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
		m_state_1p->SetBlinkTime ( 20 );
		m_state_1p->SetHalf ( T );
		AddpTask ( m_state_1p );
		GRPLST_INSERT ( m_state_1p );

		m_state_bar_1p = std::make_shared < GameGraphic > ();
		m_state_bar_1p->AddTexture_FromArchive ( U"CharaSele\\CharaSelePlayerCursor1P.png" );
		m_state_bar_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
		AddpTask ( m_state_bar_1p );
		GRPLST_INSERT ( m_state_bar_1p );

		m_state_2p = std::make_shared < GrpBlink > ();
		m_state_2p->AddTexture_FromArchive ( U"CharaSele\\2P.png" );
		m_state_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
		m_state_2p->SetBlinkTime ( 20 );
		m_state_2p->SetHalf ( T );
		AddpTask ( m_state_2p );
		GRPLST_INSERT ( m_state_2p );

		m_state_bar_2p = std::make_shared < GameGraphic > ();
		m_state_bar_2p->AddTexture_FromArchive ( U"CharaSele\\CharaSelePlayerCursor2P.png" );
		m_state_bar_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
		AddpTask ( m_state_bar_2p );
		GRPLST_INSERT ( m_state_bar_2p );



		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		m_fade_toTitle->SetAfterClear ( F );
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		m_fade_toFighting->SetAfterClear ( F );
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );

		//文字表示
		m_txt_CharacterSelect = std::make_shared < GrpBlink > ();
		m_txt_CharacterSelect->AddTexture_FromArchive ( U"CharaSele\\Text_CHARACTER_SELECT.png" );
		m_txt_CharacterSelect->SetPos ( VEC2 ( TXT_CHSL_X, TXT_CHSL_Y ) );
		m_txt_CharacterSelect->SetZ ( Z_SYS );
		m_txt_CharacterSelect->Start ();
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
		m_stageSelectTri->AddTexture_FromArchive ( U"CharaSele\\SelectTriangle.png" );
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

		m_scrlbgm_x = BGM_SCROLL_X;

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
		SND_PLAY_LOOP_BGM ( BGM_CharaSele );

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

		//設定ファイルにも記録
		pPrm->GetGameSetting().Save ();
	}


	void CharaSele::Move ()
	{
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

		Scene::Move (); 
	}


	void CharaSele::Input ()
	{
		//BackSpaceでタイトルに戻る (ESCは直接終了)
		if ( ! m_fade_toTitle->IsActive () )
		{
			if ( WND_UTL::AscKey ( VK_BACK ) )
			{
				SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

				//フェード開始
				m_fade_toTitle->StartBlackOut ( 8 );
			}
		}


		//決定
		bool b1 = m_chsl_pl_1p->IsDecided ();
		bool b2 = m_chsl_pl_2p->IsDecided ();

		//両方未決定時はステージセレクトではない
		if ( ! b1 && ! b2 )
		{
			//点滅を止める
			m_txt_StageSelect->Stop ();
			m_stageSelectTri->Stop ();
		}

		//片方が決定したらステージセレクト
		if ( b1 )
		{
			//点滅開始
			m_txt_StageSelect->Start ();
			m_stageSelectTri->Start ();

			//状態
			m_state_1p->SetPos ( CH_STT_X_1P, TXT_STSL_Y );
			m_state_bar_1p->SetPos ( CH_BAR_X_1P, TXT_STSL_Y );

			if ( CFG_PUSH_KEY ( P1_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SND_PLAY_ONESHOT_SE ( SE_select_move );
			}
			if ( CFG_PUSH_KEY ( P1_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SND_PLAY_ONESHOT_SE ( SE_select_move );
			}

			if ( CFG_PUSH_KEY ( P1_BTN0 ) )
			{
				SND_PLAY_ONESHOT_SE ( SE_select_decide );
				m_stageDecide = T;
			}
		}
		else
		{
			//状態
			m_state_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
			m_state_bar_1p->SetPos ( CH_BAR_X_1P, CH_BAR_Y );
		}

		if ( b2 )
		{
			//点滅開始
			m_txt_StageSelect->Start ();
			m_stageSelectTri->Start ();

			m_state_2p->SetPos ( CH_STT_X_2P, TXT_STSL_Y );
			m_state_bar_2p->SetPos ( CH_BAR_X_2P, TXT_STSL_Y );

			if ( CFG_PUSH_KEY ( P2_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SND_PLAY_ONESHOT_SE ( SE_select_move );
			}
			if ( CFG_PUSH_KEY ( P2_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SND_PLAY_ONESHOT_SE ( SE_select_move );
			}

			if ( CFG_PUSH_KEY ( P2_BTN0 ) )
			{
				SND_PLAY_ONESHOT_SE ( SE_select_decide );
				m_stageDecide = T;
			}
		}
		else
		{
			//状態
			m_state_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
			m_state_bar_2p->SetPos ( CH_BAR_X_2P, CH_BAR_Y );
		}

		//両者とステージを決定したらFtgMainに移行
		if ( b1 && b2 && m_stageDecide )
		{
			if ( ! m_fade_toFighting->IsActive () )
			{
				//フェード開始
				m_fade_toFighting->StartBlackOut ( 16 );
			}
		}

	}


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


}	//namespace GAME

