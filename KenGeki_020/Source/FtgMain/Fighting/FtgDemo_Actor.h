//=================================================================================================
//
//	Fighting デモ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgConst.h"	
#include "../Mutual/MutualChara.h"
#include "FtgDemo_State.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_FtgDemo = std::vector < P_FtgDemo >;

	//Actor
	class FtgDemoActor : public TASK_VEC, public std::enable_shared_from_this < FtgDemoActor >
	{
		//ステート
		P_FTG_DM_Greeting	m_Greeting;
		P_FTG_DM_GetReady	m_GetReady;
		P_FTG_DM_Main		m_Main;
		P_FTG_DM_WallBreak	m_WallBreak;
		P_FTG_DM_Down		m_Down;	
		P_FTG_DM_TimeUp		m_TimeUp;		//タイムアップ
		P_FTG_DM_TimeUpWait	m_TimeUpWait;		//タイムアップ	待機
		P_FTG_DM_Winner		m_Winner;


		//ステート監理
		VP_FtgDemo			mvp_FtgDemo;

		//現在ステート
		P_FtgDemo			mp_FtgDemo;

		//デモ共通パラメータ
		P_PRM_FTG_DEMO		mp_Param;

		//終了フラグ
		bool				m_bEnd;

	public:
		FtgDemoActor ();

		void StartGreeting ();
		void StartFighting ();

		void ParamLoad ( P_Param p );
		void Load ();
		void Do ();

		void SetwpFighting ( WP_Fighting wp ) { mp_Param->SetwpFighting ( wp ); }
		void SetpMutualChara ( P_MutualChara p ) { mp_Param->SetpMutualChara ( p ); }
		void SetpFtgGrp ( P_FtgGrp p ) { mp_Param->SetpFtgGrp ( p ); }

		void Change_Greeting_To_GetReady ();	//挨拶から準備へ
		void Change_GetReady_To_Main ();		//準備から開始へ
		void Change_Main_To_Down ();			//メインからダウンへ
		void Change_Main_To_TimeUpWait ();		//メインから時間切れ待機へ
		void Change_Main_To_TimeUp ();			//メインから時間切れへ
		void Change_TimeUp_To_Winner ();		//時間切れから勝者表示へ
		void Change_Down_To_Greeting ();		//ダウンから挨拶へ
		void Change_Down_To_Winner ();			//ダウンから勝者表示へ
		void Change_Winner_To_GetReady ();		//勝者表示から準備へ


		//Start()を用いない一時変更
		void Shift_Main_To_WallBreak ();	//メインから壁割
		void Shift_WallBreak_To_Main ();	//壁割からメイン

		
		void End_Down_To_Result ();		//戦闘終了によりリザルトへシーン移行
		bool IsEnd () const { return m_bEnd; }

		s3d::String GetName () const { return mp_FtgDemo->GetName (); }

	private:
		P_MutualChara GetpMutualChara () const { return mp_Param->GetpMutualChara (); }
	};

	using P_FtgDemoActor = std::shared_ptr < FtgDemoActor >;


}	//namespace GAME


