//=================================================================================================
//
//	CharaSele ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"
//#include "../Title/Title.h"
//#include "../FtgMain/Fighting/Fighting.h"
//#include "../Training/Training.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region CONST

	const float CharaSele::TXT_CHSL_X = 640 - 286 / 2;
	const float CharaSele::TXT_CHSL_Y = 5;
	const float CharaSele::TXT_STSL_X = 640 - 272 / 2;
	const float CharaSele::TXT_STSL_Y = 400;
	const float CharaSele::TXT_BGM_X  = 640 - 184 / 2;
	const float CharaSele::TXT_BGM_Y  = 500;
	const float CharaSele::TXT_INST_X = 640 - 516 / 2;
	const float CharaSele::TXT_INST_Y = 820;

	const float CharaSele::CH_STT_X_1P = 400;
	const float CharaSele::CH_STT_X_2P = 800;
	const float CharaSele::CH_STT_Y = 5;

#pragma endregion


	CharaSele::CharaSele ()
	{
		//BG
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"CharaSele\\CharaSele_BG.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		//Scroll
		m_scroll = std::make_shared < GameGraphic > ();
		m_scroll->SetShader ( T );
		m_scroll->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll.png" );
		m_scroll->SetPos ( 0, 0 );
		m_scroll->SetZ ( Z_BG );
		AddpTask ( m_scroll );
		GRPLST_INSERT ( m_scroll );

		//Scroll Stage
		m_scroll_Stage = std::make_shared < GameGraphic > ();
		m_scroll_Stage->SetShader ( T );
		m_scroll_Stage->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll_Stage.png" );
		m_scroll_Stage->SetPos ( 0, 400 );
		m_scroll_Stage->SetZ ( Z_BG );
		AddpTask ( m_scroll_Stage );
		GRPLST_INSERT ( m_scroll_Stage );



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
		m_state_1p = std::make_shared < GrpBlink > ();
		m_state_1p->AddTexture_FromArchive ( U"CharaSele\\1P.png" );
		m_state_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
		m_state_1p->SetBlinkTime ( 20 );
		AddpTask ( m_state_1p );
		GRPLST_INSERT ( m_state_1p );

		m_state_2p = std::make_shared < GrpBlink > ();
		m_state_2p->AddTexture_FromArchive ( U"CharaSele\\2P.png" );
		m_state_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
		m_state_2p->SetBlinkTime ( 20 );
		AddpTask ( m_state_2p );
		GRPLST_INSERT ( m_state_2p );



		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );

		//ステージセレクト
		m_stageSelect = std::make_shared < GameGraphic > ();
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Noon.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Evening.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Night.png" );
		m_stageSelect->SetPos ( VEC2 ( 640 - 128, 450 ) );
		m_stageSelect->SetZ ( Z_EFF );
		AddpTask ( m_stageSelect );
		GRPLST_INSERT ( m_stageSelect );


		//文字表示
		m_txt_CharacterSelect = std::make_shared < GrpBlink > ();
		m_txt_CharacterSelect->AddTexture_FromArchive ( U"CharaSele\\Text_CHARACTER_SELECT.png" );
		m_txt_CharacterSelect->SetPos ( VEC2 ( TXT_CHSL_X, TXT_CHSL_Y ) );
		m_txt_CharacterSelect->SetZ ( Z_SYS );
		m_txt_CharacterSelect->Start ();
		AddpTask ( m_txt_CharacterSelect );
		GRPLST_INSERT ( m_txt_CharacterSelect );

		m_txt_StageSelect = std::make_shared < GrpBlink > ();
		m_txt_StageSelect->AddTexture_FromArchive ( U"CharaSele\\Text_STAGE_SELECT.png" );
		m_txt_StageSelect->SetPos ( VEC2 ( TXT_STSL_X, TXT_STSL_Y ) );
		m_txt_StageSelect->SetZ ( Z_SYS );
		m_txt_StageSelect->Stop ();
		AddpTask ( m_txt_StageSelect );
		GRPLST_INSERT ( m_txt_StageSelect );

		m_txt_BGMSelect = std::make_shared < GrpBlink > ();
		m_txt_BGMSelect->AddTexture_FromArchive ( U"CharaSele\\Text_BGM_SELECT.png" );
		m_txt_BGMSelect->SetPos ( VEC2 ( TXT_BGM_X, TXT_BGM_Y ) );
		m_txt_BGMSelect->SetZ ( Z_SYS );
		m_txt_BGMSelect->Stop ();
		AddpTask ( m_txt_BGMSelect );
		GRPLST_INSERT ( m_txt_BGMSelect );


		//操作説明
		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"CharaSele\\Inst_CharaSele.png" );
		m_inst->SetPos ( VEC2 ( TXT_INST_X, TXT_INST_Y ) );
		m_inst->SetZ ( Z_SYS );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );
	}

	CharaSele::~CharaSele ()
	{
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
		SOUND->Stop_BGM ( BGM_CharaSele );
		SOUND->Play_Loop_BGM ( BGM_CharaSele );

		Scene::Load ();
	}

	P_GameScene CharaSele::Transit ()
	{
		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			SOUND->Stop_BGM ( BGM_CharaSele );
			Scene::Transit_Title ();
		}

		//戦闘に移行
		//フェード待機後、遷移開始
		if ( m_fade_toFighting->IsLast () )
		{
			++ m_plus_wait;
		}

		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > 15 )
			{
				SOUND->Stop_BGM ( BGM_CharaSele );

				P_Param pPrm = Scene::GetpParam ();

				if ( MODE_MAIN == pPrm->GetGameMode () )
				{
					Scene::Transit_Fighting ();
				}
				else if ( MODE_TRAINING == pPrm->GetGameMode () )
				{
					Scene::Transit_Training ();
				}

				m_plus_wait = 0;
			}
			++ m_plus_wait;
		}

		return Scene::Transit (); 
	}


	void CharaSele::ParamInit ()
	{
	}

	void CharaSele::Move ()
	{
		//背景スクロール
		m_scrl_y -= 20;
		if ( m_scrl_y < - 960 ) { m_scrl_y = 0; }
		m_scroll->SetPos ( 0, m_scrl_y );

		m_scrlStg_x -= 20;
		if ( m_scrlStg_x < - 1280 ) { m_scrlStg_x = 0; }
		m_scroll_Stage->SetPos ( m_scrlStg_x, 400 );

		//----------------------------------------------------------
		//キャラ選択、ステージ選択をパラメータに記録
		P_Param pPrm = Scene::GetpParam ();
		pPrm->SetCharaName1p ( m_chsl_pl_1p->GetName() );
		pPrm->SetCharaName2p ( m_chsl_pl_2p->GetName() );
		pPrm->SetStageName ( GetStageName () );

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

		Input ();


		Scene::Move (); 
	}


	void CharaSele::Input ()
	{
		//BackSpaceでタイトルに戻る (ESCは直接終了)
		if ( WND_UTL::AscKey ( VK_BACK ) )
		{
			SOUND->Play_SE ( SE_Sys_Cancel );

			//フェード開始
			m_fade_toTitle->SetBlackOut ( 8 );
		}

		//決定
		bool b1 = m_chsl_pl_1p->IsDecided ();
		bool b2 = m_chsl_pl_2p->IsDecided ();

		//片方が決定したらステージセレクト
		if ( b1 )
		{
			//点滅
			m_txt_StageSelect->Start ();

			//状態
			m_state_1p->SetPos ( CH_STT_X_1P, TXT_STSL_Y );

			if ( CFG_PUSH_KEY ( P1_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}
			if ( CFG_PUSH_KEY ( P1_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}

			if ( CFG_PUSH_KEY ( P1_BTN0 ) )
			{
				SOUND->Play_SE ( SE_Sys_Enter );
				m_stageDecide = T;
			}
		}
		else
		{
			//状態
			m_state_1p->SetPos ( CH_STT_X_1P, TXT_CHSL_Y );
		}

		if ( b2 )
		{
			//点滅
			m_txt_StageSelect->Start ();

			m_state_2p->SetPos ( CH_STT_X_2P, TXT_STSL_Y );

			if ( CFG_PUSH_KEY ( P2_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}
			if ( CFG_PUSH_KEY ( P2_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}

			if ( CFG_PUSH_KEY ( P2_BTN0 ) )
			{
				SOUND->Play_SE ( SE_Sys_Enter );
				m_stageDecide = T;
			}
		}
		else
		{
			//状態
			m_state_2p->SetPos ( CH_STT_X_2P, TXT_CHSL_Y );
		}

		//両者とステージを決定したらFtgMainに移行
		if ( b1 && b2 && m_stageDecide )
		{ 
			//フェード開始
			m_fade_toFighting->StartBlackOut ( 16 );
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


}	//namespace GAME

