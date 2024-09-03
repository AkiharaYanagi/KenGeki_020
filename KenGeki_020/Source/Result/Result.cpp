//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Result.h"
#include "../GameMain/SoundConst.h"

//遷移先
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Result::Result ()
	{
		m_test = std::make_shared < GameGraphic > ();
		m_test->AddTexture_FromArchive ( U"CharaSele_BG.png" );
		m_test->SetZ ( Z_BG );
		AddpTask ( m_test );
		GRPLST_INSERT ( m_test );

//		m_bg = std::make_unique < s3d::VideoTexture > ( U"Result.mp4", s3d::Loop::Yes );
//		m_bg = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::Yes );
//		GrpLst::Inst()->Clear ();
//		GrpLst::Inst()->SetupVtx ( std::move ( m_bg ) );

		m_mov = std::make_shared < GrpMov > ();
		m_mov->SetMovName ( U"Result.mp4" );
		m_mov->Loop ( T );
		m_mov->Start ();
		m_mov->SetZ ( Z_BG );
		AddpTask ( m_mov );
		GRPLST_INSERT ( m_mov );

		m_chara = std::make_shared < GameGraphic > ();
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Retsudou.png" );
		AddpTask ( m_chara );
		GRPLST_INSERT ( m_chara );
	}

	Result::~Result ()
	{
	}

	void Result::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

//		GrpLst::Inst()->StartVtx ();

		Scene::Load ();
	}

	void Result::ParamInit ()
	{
	}

	void Result::Move ()
	{
		Scene::Move ();
	}

	P_GameScene Result::Transit ()
	{
		return Scene::Transit ();
	}


}	//namespace GAME

