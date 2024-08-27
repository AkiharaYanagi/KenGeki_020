//=================================================================================================
//
//	EfClang ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//相殺時エフェクト

//	class EfClang : public GrpEf
	class EfClang : public TASK_VEC
	{
		uint32		m_index { 0 };


		P_GrpEf	m_thunder0;
		P_GrpEf	m_thunder1;
		P_GrpEf	m_circle;
		P_GrpEf	m_impact;


	public:
		EfClang ();
		EfClang ( const EfClang & rhs ) = delete;
		~EfClang ();

		void Load ();
		void Move ();

		void On ( VEC2 center );
	};

	using P_EfClang = std::shared_ptr < EfClang >;


}	//namespace GAME


