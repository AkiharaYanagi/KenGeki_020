//=================================================================================================
//
//	EfKouAtsu ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../../ExeChara/BtlParam.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//剣撃抗圧 エフェクト
	class EfKouAtsu : public GrpEf
	{
#if 0

		VEC2		m_scalingStart { 0.1f, 0.1f };
		VEC2		m_scaling { 1.f, 1.f };
		VEC2		m_vStart { 0.f, 0.f };
		VEC2		m_v { 0.f, 0.f };
		VEC2		m_a { 0.f, 0.f };

#endif // 0

		Timer		m_pchTimer;	//ピッチタイマ

	public:
		EfKouAtsu ();
		EfKouAtsu ( const EfKouAtsu & rhs ) = delete;
		~EfKouAtsu ();

		void Init ();
		void Move ();

		void On ( const BtlParam & btlPrm );
	};

	using P_EfKouAtsu = std::shared_ptr < EfKouAtsu >;


}	//namespace GAME


