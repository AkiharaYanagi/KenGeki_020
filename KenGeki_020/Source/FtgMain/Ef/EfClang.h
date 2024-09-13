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
	class EfClang : public TASK_VEC
	{
		P_GrpEfShd		m_thunder0;
		P_GrpEfShd		m_thunder1;
		P_GrpEfShd		m_circle;
		P_GrpEfShd		m_impact;

//		P_GrpEfShd		 m_test;
//		P_Grp m_test;
		double	m_r { 0 };

	public:
		EfClang ();
		EfClang ( const EfClang & rhs ) = delete;
		~EfClang ();

		void Load ();
		void Move ();

		void On ( VEC2 center );


	private:
		void SetScale ( P_Grp pGrp, const VEC2 & v );
	};

	using P_EfClang = std::shared_ptr < EfClang >;


}	//namespace GAME


