//=================================================================================================
//
// シーン
//		解放と確保を伴う状態遷移
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Scene.h"

//状態遷移先
#include "../FtgMain/FtgMain.h"
#include "../Title/Title.h"
#include "../Training/Training.h"

#if 0
#include "../CharaSele/CharaSele.h"
#include "../Introduction/Introduction.h"
#include "../Result/Result.h"
#endif // 0

//#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------

	Scene::Scene ()
		: m_bTransit ( F )
	{
	}

	Scene::~Scene ()
	{
	}

	void Scene::Load ()
	{
		//	※	継承先
		//		Load ()内で shared_from_this()をScene側に登録する
		//		Scene::Load (); も呼ぶ
		GameScene::Load ();
	}

	//状態遷移
	P_GameScene Scene::Transit ()
	{
		//他のシーンが確保されたなら遷移する
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時
		return mwp_This.lock ();
	}

	//[シーン遷移] タイトルに戻る
	void Scene::Transit_Title ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Title > ();
	}

	//[シーン遷移] ファイティングに移行
	void Scene::Transit_Fighting ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < FtgMain > ();
	}

	//[シーン遷移] トレーニングに移行
	void Scene::Transit_Training ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Training > ();
	}

#if 0
	
	//[シーン遷移] キャラセレに移行
	void Scene::Transit_CharaSele ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < CharaSele > ();
		GRPLST_LOAD ();
	}


	void Scene::Transit_Fighting ( MUTCH_MODE mode )
	{
		Transit_Fighting ();
		GetpParam ()->SetMutchMode ( mode );
	}


	//[シーン遷移] リザルトに移行
	void Scene::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Result > ();
		GRPLST_LOAD ();
	}

	//[シーン遷移] イントロに移行
	void Scene::Transit_Intro ()
	{
		GRPLST_CLEAR ();
//		mp_Transit = make_shared < Introduction > ();
		mp_Transit = make_shared < Intro_Img > ();
		GRPLST_LOAD ();
	}
#endif // 0

	//====================================================================
	SceneManager::SceneManager()
	{
		START_MODE startMode;

		//テスト用 開始状態選択
//		startMode = START_TITLE;
//		startMode = START_CHARA_SELE;
//		startMode = START_BATTLE;
		startMode = START_TRAINING;
#if 0
//		startMode = START_INTRO;
//		startMode = START_RESULT;
//		startMode = START_DEMO;
//		startMode = TEST_VOID;
#endif // 0


		//最初のシーンを設定ファイルから取得する
		m_pParam = std::make_shared < Param > ();	//パラメータ
#if 0
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		startMode = stgs.GetStartMode ();
#endif // 0


		//開始シーンの選択
		P_Scene pScene = nullptr;

		switch ( startMode )
		{
		//---------------------------------------------
		//タイトルから開始
		case START_TITLE:
			pScene = std::make_shared < Title > ();
		break;

		//---------------------------------------------
		//バトルから開始
		case START_BATTLE:
			pScene = std::make_shared < FtgMain > ();
		break;

#if 0
		//---------------------------------------------
		//キャラセレから開始
		case START_CHARA_SELE:
			pScene = std::make_shared < CharaSele > ();
		break;
#endif // 0

		//---------------------------------------------
		case START_TRAINING:
			//トレーニングから開始
			pScene = std::make_shared < Training > ();
		break;


		//---------------------------------------------
		default: break;

		}


#if 0

		switch ( startMode )
		{
		case START_TITLE_INTRO:
			//タイトルから開始
			pScene = make_shared < Title > ();
			break;

		case START_INTRO:


			//イントロから開始
//			pScene = make_shared < Introduction > ();
			pScene = make_shared < Intro_Img > ();

			
			break;

		case START_BATTLE:
			//バトルから開始
			pScene = make_shared < FtgMain > ();
			break;

		case START_RESULT:
			//リザルトから開始
			pScene = make_shared < Result > ();
			break;

		case START_TRAINING:
			//トレーニングから開始
			pScene = make_shared < Training > ();
			break;

#if 0
		case START_DEMO:
			//デモから開始
			pScene = make_shared < Title > ();
			break;

		case TEST_VOID:
			//テスト：空のシーン
			pScene = make_shared < TestScene > ();
			break;
#endif // 0

		}

#endif // 0

		//シーンの設定
		SetScene ( pScene );
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Load ()
	{
		//最初のシーンにパラメータを設定する
		P_GameScene pScene = GetpScene ();
		pScene->SetpParam ( m_pParam );
		pScene->ParamInit ();

		GameSceneManager::Load ();
	}


}	//namespace GAME

