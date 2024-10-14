//=================================================================================================
//
//	ExeChara ステート
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//前方宣言	(循環参照なので weak_ptr )
	class ExeChara_Actor;	using WP_ExeChara_Actor = std::weak_ptr < ExeChara_Actor >;
	class ExeChara;	using WP_ExeChara = std::weak_ptr < ExeChara >;

	//Param
	class ExeChara_Param
	{
		WP_ExeChara_Actor	mwp_ExeChara_Actor;
		WP_ExeChara			mwp_ExeChara;

	public:
		void SetwpExeChara_Actor ( WP_ExeChara_Actor p ) { mwp_ExeChara_Actor = p; }
		WP_ExeChara_Actor GetwpExeChara_Actor () const { return mwp_ExeChara_Actor; }

		void SetwpExeChara ( WP_ExeChara p ) { mwp_ExeChara = p; }
		WP_ExeChara GetwpExeChara () const { return mwp_ExeChara; }
	};
	using P_ExeChara_Param = std::shared_ptr < ExeChara_Param >;


	//=====================================================
	//State
	class ExeChara_State
	{
	protected:
		P_ExeChara_Param	mp_PrmExeChara;
	public:
		ExeChara_State () {}
		ExeChara_State ( const ExeChara_State & rhs ) = delete;
		~ExeChara_State () {}

		virtual void Start () {}
		virtual void Do () {}
		virtual void PreScriptMove () {}
		virtual void RectMove () {}
		virtual void PostScriptMove () {}
		virtual bool SkipDecision () const { return F; }

		virtual s3d::String GetName () const { return U"State"; }

		void SetpPrm ( P_ExeChara_Param p ) { mp_PrmExeChara = p; }

		WP_ExeChara GetwpExeChara () const { return mp_PrmExeChara->GetwpExeChara (); }

		//共通：入力なしPreScriptMove
		void PreScriptMove_NoInput ();
		//共通：ライフ判定なしPostScriptMove
		void PostScriptMove_NoLifeCheck ();

	};
	using P_ExeChara_State = std::shared_ptr < ExeChara_State >;
	using VP_ExeChara_State = std::vector < P_ExeChara_State >;

	//=====================================================
	//State_Derivered
	
	
	
	//演出　開始

	class CHST_Start : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"Start"; }
	};
	using P_CHST_Start = std::shared_ptr < CHST_Start >;

	//------------------------------------------------

	//演出　挨拶

	class CHST_Greeting : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"Greeting"; }
		void Start ();
		void PreScriptMove ();
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_Greeting = std::shared_ptr < CHST_Greeting >;

	//------------------------------------------------
	//演出　ゲットレディ

	class CHST_GetReady : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"GetReady"; }
		void Start ();
		void PreScriptMove ();
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_GetReady = std::shared_ptr < CHST_GetReady >;


	//==========================================================================
	//------------------------------------------------
	//バトル　メイン状態
	class CHST_Main : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"BattleMain"; }
		void Start ();
		void PreScriptMove ();
		void RectMove ();
		void PostScriptMove ();
	};
	using P_CHST_Main = std::shared_ptr < CHST_Main >;

	//------------------------------------------------
	//バトル　一時停止
	class CHST_ScpStop : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"Stop"; }
		void PreScriptMove ();
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_ScpStop = std::shared_ptr < CHST_ScpStop >;

	//------------------------------------------------
	//バトル　壁割
	class CHST_WallBreak : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"WallBreak"; }
		void PreScriptMove ();
		void PostScriptMove ();
	};
	using P_CHST_WallBreak = std::shared_ptr < CHST_WallBreak >;

	//------------------------------------------------
	//バトル　スロウスキップ状態(スロウ時に飛ばすフレーム処理のとき)
	class CHST_Slow_Skip : public ExeChara_State
	{
	public:
		s3d::String GetName () const { return U"SlowSkip"; }
		void PreScriptMove ();
		void RectMove ();
		void PostScriptMove ();
	};
	using P_CHST_Slow_Skip = std::shared_ptr < CHST_Slow_Skip >;


	//==========================================================================
	//------------------------------------------------
	//終了の前の待機
	class CHST_EndWait : public ExeChara_State
	{
	public:
		void Start ();
		void PreScriptMove ();
		//■ void RectMove ();
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_EndWait = std::shared_ptr < CHST_EndWait >;
	//------------------------------------------------

	//敗北ダウン状態
	class CHST_Down : public ExeChara_State
	{
	public:
		void Start ();
		void PreScriptMove ();
		//■ void RectMove () {}
		void Do ();
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_Down = std::shared_ptr < CHST_Down >;
	//------------------------------------------------

	//ダウン中待機
	class CHST_DownWait : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		//■ void ScriptRectMove () {}
		void PostScriptMove () {}
		bool SkipDecision () const { return T; }
	};
	using P_CHST_DownWait = std::shared_ptr < CHST_DownWait >;
	//------------------------------------------------
	//勝利表示の前の待機
	class CHST_WinWait : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		//■ void RectMove () {}
		void PostScriptMove () {}
		bool SkipDecision () const { return T; }
	};
	using P_CHST_WinWait = std::shared_ptr < CHST_WinWait >;
	//------------------------------------------------

	//勝者表示
	class CHST_Win : public ExeChara_State
	{
	public:
		void Start ();
		void PreScriptMove ();
		//■ void RectMove () {}
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_Win = std::shared_ptr < CHST_Win >;
	//------------------------------------------------

	class CHST_WinEnd : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		//■ void RectMove () {}
		void PostScriptMove () {}
		bool SkipDecision () const { return T; }
	};
	using P_CHST_WinEnd = std::shared_ptr < CHST_WinEnd >;
	//------------------------------------------------

	class CHST_TimeUp : public ExeChara_State
	{
	public:
		void Start ();
		void PreScriptMove ();
		//■ void RectMove () {}
		void PostScriptMove ();
		bool SkipDecision () const { return T; }
	};
	using P_CHST_TimeUp = std::shared_ptr < CHST_TimeUp >;
	//------------------------------------------------


	//=====================================================


}	//namespace GAME

