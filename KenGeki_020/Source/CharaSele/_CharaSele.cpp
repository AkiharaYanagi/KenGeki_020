//=================================================================================================
//
//	_CharaSele ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region CONST

	//キャラセレ
	const float _CharaSele::TXT_CHSL_X = 640 - 270 / 2;
	const float _CharaSele::TXT_CHSL_Y = 24;

	//キャラ別
	const float _CharaSele::CH_INDEX_X_1P = 0    + 100;
	const float _CharaSele::CH_INDEX_X_2P = 1280 - 100 - 194;
	const float _CharaSele::CH_INDEX_Y = 5;

	const float _CharaSele::CH_BAR_X_1P = 405;
	const float _CharaSele::CH_BAR_X_2P = 405;
	const float _CharaSele::CH_BAR_Y = 0;

	//ステージセレクト
	const float _CharaSele::STG_BG_X = 0;
	const float _CharaSele::STG_BG_Y = 385;
	const float _CharaSele::TXT_STSL_X = 640 - 260 / 2;
	const float _CharaSele::TXT_STSL_Y = 390;
	const float _CharaSele::STG_X = 640 - 256 / 2;
	const float _CharaSele::STG_Y = 420;
	const float _CharaSele::STG_TRI_X = (1280 - 335) * 0.5f;
	const float _CharaSele::STG_TRI_Y = STG_Y + 50;

	//BGMセレクト
	const float _CharaSele::BGM_SCROLL_X = 1280;
	const float _CharaSele::BGM_SCROLL_Y = 570;
	const float _CharaSele::TXT_BGM_X  = 640 - 184 / 2;
	const float _CharaSele::TXT_BGM_Y  = 572;
	const float _CharaSele::BGM_X = 640 - 225;
	const float _CharaSele::BGM_Y = 605;
	const float _CharaSele::BGM_TRI_X = (1280 - 450) * 0.5f;
	const float _CharaSele::BGM_TRI_Y = BGM_Y + 4;

	//操作説明
	const float _CharaSele::INST_X = 0;
	const float _CharaSele::INST_Y = 960 - 27;

#pragma endregion


	_CharaSele::_CharaSele ()
	{
		//BG(全体)
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"CharaSele\\CharaSele_BG.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		//CharaFace
		m_charaFace = std::make_shared < GameGraphic > ();
		m_charaFace->AddTexture_FromArchive ( U"CharaSele\\CharaFace.png" );
		m_charaFace->SetPos ( (1280 - 455) / 2, 70 );
		m_charaFace->SetZ ( Z_EFF );
		AddpTask ( m_charaFace );
		GRPLST_INSERT ( m_charaFace );

		//CharaTx
		m_img_cmn = std::make_shared < CharaSele_Image_Common > ();

		//Player
		m_player_1p = std::make_shared < _CharaSele_Player > ();
		m_player_1p->PlayerInit ( PLAYER_ID_1 );
		m_player_1p->LoadTx ( m_img_cmn );

		m_player_2p = std::make_shared < _CharaSele_Player > ();
		m_player_2p->PlayerInit ( PLAYER_ID_2 );
		m_player_2p->LoadTx ( m_img_cmn );

		//1P2P表示
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

		m_txt_StageSelect = std::make_shared < GrpBlink > ();
		m_txt_StageSelect->AddTexture_FromArchive ( U"CharaSele\\Text_STAGE_SELECT.png" );
		m_txt_StageSelect->SetPos ( VEC2 ( TXT_STSL_X, TXT_STSL_Y ) );
		m_txt_StageSelect->SetZ ( Z_SYS );
		m_txt_StageSelect->Stop ();
		m_txt_StageSelect->SetHalf ( T );
		AddpTask ( m_txt_StageSelect );
		GRPLST_INSERT ( m_txt_StageSelect );

		m_txt_BGMSelect = std::make_shared < GrpBlink > ();
		m_txt_BGMSelect->AddTexture_FromArchive ( U"CharaSele\\Text_BGM_SELECT.png" );
		m_txt_BGMSelect->SetPos ( VEC2 ( TXT_BGM_X, TXT_BGM_Y ) );
		m_txt_BGMSelect->SetZ ( Z_SYS );
		m_txt_BGMSelect->Stop ();
		m_txt_BGMSelect->SetHalf ( T );
		AddpTask ( m_txt_BGMSelect );
		GRPLST_INSERT ( m_txt_BGMSelect );


	}


	_CharaSele::~_CharaSele ()
	{
	}


	void _CharaSele::ParamInit ()
	{
	}

	void _CharaSele::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		Scene::Load ();
	}

	P_GameScene _CharaSele::Transit ()
	{
		return shared_from_this ();
	}


}	//namespace GAME

