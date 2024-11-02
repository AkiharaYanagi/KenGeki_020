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
#include "../CharaSele/CharaSele.h"
#include "../Result/Result.h"

#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------

	Scene::Scene ()
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

	void Scene::Transit_Fighting ( MUTCH_MODE mode )
	{
		GetpParam ()->SetMutchMode ( mode );
		Transit_Fighting ();
	}

	//[シーン遷移] トレーニングに移行
	void Scene::Transit_Training ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Training > ();
	}
	
	//[シーン遷移] キャラセレに移行
	void Scene::Transit_CharaSele ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < CharaSele > ();
	}

	//[シーン遷移] リザルトに移行
	void Scene::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Result > ();
	}


	//====================================================================
	SceneManager::SceneManager()
	{
		START_MODE startMode;

		//テスト用 開始状態選択
		startMode = START_TITLE;
//		startMode = START_CHARA_SELE;
//		startMode = START_BATTLE;
//		startMode = START_TRAINING;
//		startMode = START_RESULT;


		//ゲーム共通パラメータ
		m_pParam = std::make_shared < Param > ();

		//最初のシーンを設定ファイルから取得する
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		startMode = stgs.GetStartMode ();


		if ( startMode == START_TITLE )
		{
			//全キャラデータを事前読込
			// ここで読込しないとき、バトルメインでキャラの個別読込
//			m_pParam->LoadCharaData_All ();
		}


		//デバッグ表示オン/オフ 初期状態
		//ExeChara 1p/2p のとき、1pの値を2pで上書きに注意
//		DBGOUT_WND_ON (); 
		DBGOUT_WND_OFF ();



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

		//---------------------------------------------
		//キャラセレから開始
		case START_CHARA_SELE:
			pScene = std::make_shared < CharaSele > ();
		break;

		//---------------------------------------------
		case START_TRAINING:
			//トレーニングから開始
			pScene = std::make_shared < Training > ();
		break;

		//---------------------------------------------
		case START_RESULT:
			//リザルトから開始
			pScene = std::make_shared < Result > ();
		break;

		//---------------------------------------------
		default: break;

		}

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

	void SceneManager::Move ()
	{
		//デバッグ表示切替トグル
		static bool bDispDebug = T;
		static bool pre_bDispDebug = F;
		static bool is_bDispDebug = F;

		is_bDispDebug = ( WND_UTL::AscKey ( VK_F8 ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispDebug && is_bDispDebug )	// false -> true
		{
			if ( bDispDebug )
			{
				//デバッグ表示オフ
				DBGOUT_WND_OFF ();
				bDispDebug = F;
			}
			else
			{
				//デバッグ表示オン
				DBGOUT_WND_ON ();
				bDispDebug = T;
			}
		}
		//今回の保存
		pre_bDispDebug = is_bDispDebug;

		GameSceneManager::Move ();
	}


}	//namespace GAME

