//=================================================================================================
//
//	FtgGrp ヘッダファイル
//		Fighting 全体共通画面処理
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
	class FtgGrp : public TASK_VEC
	{
		//タイマ
		Timer	m_tmrScpStop;		//一時停止
		Timer	m_tmrBlackOut;		//暗転
		Timer	m_tmrWhiteOut;		//白転
		Timer	m_tmrSlow;			//スロウ
		Timer	m_tmrVibration;		//振動

//		P_Timer			m_tmrBlackOut;		//暗転
		P_PrmRect		m_bg_black;			//暗転用
		P_PrmRect		m_bg_White;			//白転用


		bool	m_WhiteOut { F };	//白転
		P_FadeRect	m_fade_white;


		bool	m_wallbreak { F };	//壁割
		PLAYER_ID	m_WB_Plyaer { _PLAYER_NUM };	//壁を割った側のプレイヤ

		bool	m_overdrive { F };	//超必殺演出

		//test 動画
		std::unique_ptr < s3d::VideoTexture > mp_vtx;



	public:
		FtgGrp ();
		FtgGrp ( const FtgGrp & rhs ) = delete;
		~FtgGrp ();

		void Load ();
		void Init ();
		void Move ();

//		GET_SET ( bool, GetScpStop, SetScpStop, m_ScpStop )
//		GET_SET ( bool, GetBlackOut, SetBlackOut, m_BrackOut )
		GET_SET ( bool, GetWhiteOut, SetWhiteOut, m_WhiteOut )
//		GET_SET ( bool, GetSlow, SetSlow, m_Slow )
		GET_SET ( bool, GetOverDrive, SetOverDrive, m_overdrive )
		GET_SET ( bool, GetWallBreak, SetWallBreak, m_wallbreak )
		GET_SET ( PLAYER_ID, GetWB_Player, SetWB_Player, m_WB_Plyaer )

		//---------------------------------------
		void StartScpStop ( UINT i ) { m_tmrScpStop.Start ( i ); }
		bool IsActive_ScpStop () const { return m_tmrScpStop.IsActive (); }
		bool IsLast_ScpSopt () const { return m_tmrScpStop.IsLast (); }

		//---------------------------------------
		void StartBlackOut ( UINT i ) { m_tmrBlackOut.Start ( i ); }
		bool IsActive_BlackOut () const { return m_tmrBlackOut.IsActive (); }

		//---------------------------------------
		void StartWhiteOut ( UINT i ) { m_tmrWhiteOut.Start ( i ); }
		bool IsActive_WhiteOut () const { return m_tmrWhiteOut.IsActive (); }

		//---------------------------------------
		void StartSlow ( UINT i ) { m_tmrSlow.Start ( i ); }
		bool IsSlowStart () const { return m_tmrSlow.IsStart (); }
		bool IsSlowLast () const { return m_tmrSlow.IsLast ();	}
		void InitSlow () { m_tmrSlow.Clear (); };

		//---------------------------------------
		void StartVibration ( UINT i ) { m_tmrVibration.Start ( i ); }
	};

	using P_FtgGrp = std::shared_ptr < FtgGrp >;


}	//namespace GAME


