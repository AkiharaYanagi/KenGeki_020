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
		bool	m_ScpStop { F };	//一時停止


		//bool	m_BrackOut { F };	//暗転
		Timer	m_tmrBlackOut;		//暗転


		bool	m_WhiteOut { F };	//白転
		bool	m_Slow { F };		//スロウ
		Timer	m_tmrSlow;			//スロウ
		Timer	m_tmrStop;			//ストップ

		bool	m_wallbreak { F };	//壁割
		PLAYER_ID	m_WB_Plyaer { _PLAYER_NUM };	//壁を割ったプレイヤ

		bool	m_overdrive { F };	//超必殺演出

		//test 動画
		std::unique_ptr < s3d::VideoTexture > mp_vtx;

		P_FadeRect	m_fade_white;

	public:
		FtgGrp ();
		FtgGrp ( const FtgGrp & rhs ) = delete;
		~FtgGrp ();

		void Load ();
		void Init ();
		void Move ();

		GET_SET ( bool, GetScpStop, SetScpStop, m_ScpStop )
//		GET_SET ( bool, GetBlackOut, SetBlackOut, m_BrackOut )
		GET_SET ( bool, GetWhiteOut, SetWhiteOut, m_WhiteOut )
		GET_SET ( bool, GetSlow, SetSlow, m_Slow )
		GET_SET ( bool, GetOverDrive, SetOverDrive, m_overdrive )
		GET_SET ( bool, GetWallBreak, SetWallBreak, m_wallbreak )
		GET_SET ( PLAYER_ID, GetWB_Player, SetWB_Player, m_WB_Plyaer )


		//---------------------------------------
		void StartSlow ( UINT i ) { m_tmrSlow.Start ( i ); }
		bool IsSlowStart () const { return m_tmrSlow.IsStart (); }
		bool IsSlowLast () const { return m_tmrSlow.IsLast ();	}
		void InitSlow () { m_tmrSlow.Clear (); };

		//---------------------------------------
		void StartStop ( UINT i ) { m_tmrStop.Start ( i ); }
		bool IsTmrActive () const { return m_tmrStop.IsActive (); }

		//---------------------------------------
		void StartBlackOut ( UINT i ) { m_tmrBlackOut.Start ( i ); }
		bool IsActive_BlackOut () const { return m_tmrBlackOut.IsActive (); }
	};

	using P_FtgGrp = std::shared_ptr < FtgGrp >;


}	//namespace GAME


