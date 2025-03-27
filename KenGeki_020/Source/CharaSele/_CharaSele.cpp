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

