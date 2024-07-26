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
#include "FtgConst.h"	
#include "MutualChara.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//アクタ　前方宣言
	class FtgDemoActor; using WP_FtgDemoActor = std::weak_ptr < FtgDemoActor >;

	//=====================================================
	//param
	class FtgDemoParam
	{
		P_MutualChara		m_mutualChara;
		WP_FtgDemoActor		m_ftgDemoActor;
		P_Param				m_pSceneParam;	//シーン共通パラメータ		

	public:
		
		void SetpMutualChara ( P_MutualChara p ) { m_mutualChara = p; }
		P_MutualChara GetpMutualChara () const { return m_mutualChara; }

		void SetwpFtgDemoActor ( WP_FtgDemoActor p ) { m_ftgDemoActor = p; }
		WP_FtgDemoActor GetwpFtgDemoActor () const { return m_ftgDemoActor; }

		void SetpSceneParam ( P_Param p ) { m_pSceneParam = p; }
		P_Param GetpSceneParam () const { return m_pSceneParam; }
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

		P_GrpDemo MakeGrpValue ( LPCTSTR txName );
		P_MutualChara GetpMutualChara () const { return m_prmFtgDemo->GetpMutualChara (); }
		WP_FtgDemoActor GetwpFtgDemoActor () const { return m_prmFtgDemo->GetwpFtgDemoActor (); }

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
	};
	using P_FTG_DM_Greeting = std::shared_ptr < FTG_DM_Greeting >;

	//------------------------------------------------
	//準備
	class FTG_DM_GetReady : public FtgDemoState
	{
		P_GrpDemo		m_grpGetReady;
//		P_GrpAcv		m_grpClock;
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
	};
	using P_FTG_DM_GetReady = std::shared_ptr < FTG_DM_GetReady >;

	//------------------------------------------------
	//開始
	class FTG_DM_Attack : public FtgDemoState
	{
		P_GrpDemo		m_grpAttack;
	public:
		FTG_DM_Attack ();
		FTG_DM_Attack ( const FTG_DM_Attack & rhs ) = delete;
		~FTG_DM_Attack () {}

		void Start ();
		void Do ();
	};
	using P_FTG_DM_Attack = std::shared_ptr < FTG_DM_Attack >;

	//------------------------------------------------
	//メイン
	class FTG_DM_Main : public FtgDemoState
	{
	public:
		void Start ();
		void Do ();
	};
	using P_FTG_DM_Main = std::shared_ptr < FTG_DM_Main >;

	//------------------------------------------------
	//特殊演出 (壁割り)
	class FTG_DM_WallBreak : public FtgDemoState
	{
		//タイマ
		P_Timer		m_timer;

	public:
		FTG_DM_WallBreak();
		void Start ();
		void Do ();
	};
	using P_FTG_DM_WallBreak = std::shared_ptr < FTG_DM_WallBreak >;

	//------------------------------------------------
	//ダウン
	class FTG_DM_Down : public FtgDemoState
	{
		P_GrpDemo		m_grpDown;
	public:
		FTG_DM_Down ();
		FTG_DM_Down ( const FTG_DM_Down & rhs ) = delete;
		~FTG_DM_Down () {}

		void Start ();
		void Do ();
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
	};
	using P_FTG_DM_Winner = std::shared_ptr < FTG_DM_Winner >;



}	//namespace GAME


