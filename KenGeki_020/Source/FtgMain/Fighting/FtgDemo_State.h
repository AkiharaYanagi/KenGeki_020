//=================================================================================================
//
//	Fighting デモ
//		バトル中、共通状態
//		開始、終了など
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgConst.h"	
#include "../Mutual/MutualChara.h"
#include "WallBreak.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//アクタ　前方宣言
	class Fighting; using WP_Fighting = std::weak_ptr < Fighting >;
	class FtgDemoActor; using WP_FtgDemoActor = std::weak_ptr < FtgDemoActor >;

	//=====================================================
	//param
	class FtgDemoParam
	{
		WP_Fighting			m_fighting;		//戦闘全般
		P_MutualChara		m_mutualChara;	//キャラ相互
		WP_FtgDemoActor		m_ftgDemoActor;	//アクタ（Weak_ptr）
		P_Param				m_pSceneParam;	//シーン共通パラメータ
		P_FtgGrp			m_ftgGrp;		//共通グラフィック処理

	public:

		void SetwpFighting ( WP_Fighting p ) { m_fighting = p; }
		WP_Fighting GetwpFighting () const { return m_fighting; }

		void SetpMutualChara ( P_MutualChara p ) { m_mutualChara = p; }
		P_MutualChara GetpMutualChara () const { return m_mutualChara; }

		void SetwpFtgDemoActor ( WP_FtgDemoActor p ) { m_ftgDemoActor = p; }
		WP_FtgDemoActor GetwpFtgDemoActor () const { return m_ftgDemoActor; }

		void SetpSceneParam ( P_Param p ) { m_pSceneParam = p; }
		P_Param GetpSceneParam () const { return m_pSceneParam; }

		void SetpFtgGrp ( P_FtgGrp p ) { m_ftgGrp = p; }
		P_FtgGrp GetpFtgGrp () const { return m_ftgGrp; }
	};

	using P_PRM_FTG_DEMO = std::shared_ptr < FtgDemoParam >;

	//=====================================================
	//State基準クラス
	class FtgDemoState : public TASK_VEC
	{
	protected:
		P_PRM_FTG_DEMO		m_prmFtgDemo;
	public:
		FtgDemoState () {}
		FtgDemoState ( const FtgDemoState & rhs ) = delete;
		~FtgDemoState () {}

		virtual void Do () {}
		void SetpPrm ( P_PRM_FTG_DEMO p ) { m_prmFtgDemo = p; }

		WP_Fighting GetwpFighting () const { return m_prmFtgDemo->GetwpFighting (); }
		P_MutualChara GetpMutualChara () const { return m_prmFtgDemo->GetpMutualChara (); }
		WP_FtgDemoActor GetwpFtgDemoActor () const { return m_prmFtgDemo->GetwpFtgDemoActor (); }
		P_FtgGrp GetpFtgGrp () const { return m_prmFtgDemo->GetpFtgGrp (); }

		virtual s3d::String GetName () const { return s3d::String { U"FtgDemoState"}; }

	protected:
		P_GrpDemo MakeGrpValue ( s3d::String txName );	//内部オブジェクト作成用
	};
	using P_FtgDemo = std::shared_ptr < FtgDemoState >;

	//=====================================================

	//State_Derivered

	//------------------------------------------------
	//開幕挨拶
	class FTG_DM_Greeting : public FtgDemoState
	{
		//タイマ
		P_Timer		m_timer;

	public:
		FTG_DM_Greeting ();
		FTG_DM_Greeting ( const FTG_DM_Greeting & rhs ) = delete;
		~FTG_DM_Greeting () {}
		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_Greeting"}; }
	};
	using P_FTG_DM_Greeting = std::shared_ptr < FTG_DM_Greeting >;

	//------------------------------------------------
	//準備
	class FTG_DM_GetReady : public FtgDemoState
	{
		P_GrpDemo		m_grpGetReady;
		P_Timer			m_timer;
		static const UINT		COUNT;
		static const UINT		COUNT_D;
	public:
		FTG_DM_GetReady ();
		FTG_DM_GetReady ( const FTG_DM_GetReady & rhs ) = delete;
		~FTG_DM_GetReady () {}
		
		void Start ();
		void Do ();
		void Final ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_GetReady"}; }
	};
	using P_FTG_DM_GetReady = std::shared_ptr < FTG_DM_GetReady >;

	//------------------------------------------------
	//メイン
	class FTG_DM_Main : public FtgDemoState
	{
		P_GrpDemo		m_grpAttack;
	public:
		FTG_DM_Main ();
		void Start ();
		void Do ();
		void Final ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_Main"}; }
	};
	using P_FTG_DM_Main = std::shared_ptr < FTG_DM_Main >;

	//------------------------------------------------
	//特殊演出 (一時停止)
	class FTG_DM_ScpStop : public FtgDemoState
	{
		//壁割エフェクト
		P_WallBreak		m_wallBreakEf;

		//タイマ
		P_Timer		m_timer;

	public:
		FTG_DM_ScpStop () {}
		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_ScpStop"}; }
	};
	using P_FTG_DM_ScpStop = std::shared_ptr < FTG_DM_ScpStop >;

	//------------------------------------------------
	//特殊演出 (壁割り)
	class FTG_DM_WallBreak : public FtgDemoState
	{
		//壁割エフェクト
		P_WallBreak		m_wallBreakEf;

		//タイマ
		P_Timer		m_timer;

	public:
		FTG_DM_WallBreak ();
		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_WallBreak"}; }
	};
	using P_FTG_DM_WallBreak = std::shared_ptr < FTG_DM_WallBreak >;

	//------------------------------------------------
	//ダウン
	class FTG_DM_Down : public FtgDemoState
	{
		P_GrpDemo	m_grpDown;
		P_Timer		m_timer;	//タイマ
	public:
		FTG_DM_Down ();
		FTG_DM_Down ( const FTG_DM_Down & rhs ) = delete;
		~FTG_DM_Down () {}

		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_Down"}; }
	};
	using P_FTG_DM_Down = std::shared_ptr < FTG_DM_Down >;

	//------------------------------------------------
	//タイムアップ 待機
	class FTG_DM_TimeUpWait : public FtgDemoState
	{
		P_GrpDemo		m_grpTimeUp;
	public:
		FTG_DM_TimeUpWait ();
		FTG_DM_TimeUpWait ( const FTG_DM_TimeUpWait & rhs ) = delete;
		~FTG_DM_TimeUpWait () {}

		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_TimeUpWait"}; }
	};
	using P_FTG_DM_TimeUpWait = std::shared_ptr < FTG_DM_TimeUpWait >;

	//------------------------------------------------
	//タイムアップ
	class FTG_DM_TimeUp : public FtgDemoState
	{
		P_Timer		m_timer;
	public:
		FTG_DM_TimeUp ();
		FTG_DM_TimeUp ( const FTG_DM_TimeUp & rhs ) = delete;
		~FTG_DM_TimeUp () {}

		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_TimeUp"}; }
	};
	using P_FTG_DM_TimeUp = std::shared_ptr < FTG_DM_TimeUp >;

	//------------------------------------------------
	//勝者表示
	class FTG_DM_Winner : public FtgDemoState
	{
		P_Timer			m_dispTimer;
		P_GrpDemo		m_grpWinner;
		P_GrpDemo		m_grp1p;
		P_GrpDemo		m_grp2p;
		P_GrpDemo		m_grpDraw;

		P_FadeRect		m_fade;

	public:
		FTG_DM_Winner ();
		FTG_DM_Winner ( const FTG_DM_TimeUp & rhs ) = delete;
		~FTG_DM_Winner () {}

		void Start ();
		void Do ();
		s3d::String GetName () const { return s3d::String { U"FTG_DM_Winner"}; }
	};
	using P_FTG_DM_Winner = std::shared_ptr < FTG_DM_Winner >;



}	//namespace GAME


