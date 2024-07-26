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
	class FtgGrp
	{
		bool	m_BrackOut { F };		//暗転
		bool	m_WhiteOut { F };		//白転
		bool	m_Slow { F };			//スロウ
		Timer	m_tmrSlow;				//スロウ
		Timer	m_tmrStop;	//ストップ

	public:
		FtgGrp ();
		FtgGrp ( const FtgGrp & rhs ) = delete;
		~FtgGrp ();

		void Init ();
		void Move ();

		GET_SET ( bool, GetBlackOut, SetBlackOut, m_BrackOut )
		GET_SET ( bool, GetWhiteOut, SetWhiteOut, m_WhiteOut )
		GET_SET ( bool, GetSlow, SetSlow, m_Slow )


		//---------------------------------------
		void StartSlow ();
		bool IsSlowStart () const { return m_tmrSlow.IsStart (); }
		bool IsSlowLast () const { return m_tmrSlow.IsLast ();	}
		void InitSlow () { m_tmrSlow.Clear (); };

		//---------------------------------------
		void StartStop ( UINT i );
		bool IsTmrActive () const { return m_tmrStop.IsActive (); }

	};

	using P_FtgGrp = std::shared_ptr < FtgGrp >;


}	//namespace GAME


