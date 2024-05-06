//=================================================================================================
//
// シーンヘッダ
//		ゲームシーンを用いた状態遷移
//		ゲーム内定義のパラメータ(Param)を共通で扱う
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
//#include "GameSettingFile.h"
#include "Param.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------
	//前方宣言
	class Scene;
	using WP_Scene = std::weak_ptr < Scene >;
	using P_Scene = std::shared_ptr < Scene >;


	//-----------------------------------------------
	//ゲーム場面
	class Scene : public GameScene //, public enable_shared_from_this < Scene >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_Scene	mwp_This;
		P_Scene		mp_Transit;		//遷移可能な次のシーン

		//===========================================================
		bool	m_bTransit;

	public:
		Scene ();
		Scene ( const Scene & rhs ) = delete;
		~Scene ();

		//==================================================
		//	Scene共通
		//==================================================

		//-----------------------------------------------
		//	※	継承先クラス宣言において
		//		, public enable_shared_from_this < ClassName >
		//		を多重継承しておく
		
		//-----------------------------------------------
		//	※	継承先
		//		Load ()内で shared_from_this()をScene側に登録する
		//		Scene::Load (); も呼ぶ
		void Load ();

		//-----------------------------------------------
		//	※	Transit () をオーバーライドするとき戻値を
		//			return Scene::Transit ();
		//		とする
		P_GameScene Transit ();

		//==================================================

		//共通パラメータ
		void SetpParam ( P_Param&& pParam )
		{
			GameScene::SetpParam ( pParam ); 
		}
		P_Param GetpParam ()
		{
			P_GameParam pgp = GameScene::GetpParam (); 
			P_Param pp = dynamic_pointer_cast < Param > ( pgp );
			return pp; 
		}

		//遷移
		bool GetTransit () const { return m_bTransit; }
		void SetTransit ( bool b ) { m_bTransit = b; }

		WP_Scene GetwpThis () { return mwp_This; }
		void SetwpParentScene ( WP_Scene wp ) { mwp_This = wp; }
		void SetwpThis ( WP_Scene wp ) { mwp_This = wp; }

		//メニュ用シーン移項
		void Transit_Title ();		//タイトルに戻る
		void Transit_Intro ();		//イントロに移行
		void Transit_Fighting ();	//ファイティングに移行
		void Transit_Fighting ( MUTCH_MODE mode );		//ファイティングに移行(VSモード指定)
		void Transit_Training ();	//トレーニングに移行
		void Transit_CharaSele ();	//キャラセレに移行
		void Transit_Result ();		//リザルトに移行
	};



#if 0
	//test
//	class TestScene : public Scene, public enable_shared_from_this < TestScene >
	class TestScene : public enable_shared_from_this < TestScene >
	{
	public:
		void ParamInit () {}
//		P_GameScene Transit () { return shared_from_this (); }
	};
	using P_TestScene = std::shared_ptr < TestScene >;
#endif // 0


	//==================================================================
	//ゲーム状態遷移管理
	class SceneManager	: public GameSceneManager
	{
		P_Param		m_pParam;	//シーン共通パラメータ

	public:
		SceneManager ();
		SceneManager ( const SceneManager& rhs ) = delete;
		~SceneManager ();

		void Load ();

		//シーン共通パラメータ
		void SetpParam ( P_Param&& pParam ) { m_pParam = pParam; }
		P_Param GetpParam () { return m_pParam; }
	};


}	//namespace GAME

