//=================================================================================================
//	Behavior ヘッダファイル
//=================================================================================================
#pragma once
//#include "Game.h"
//#include "GameTexture.h"
//#include "Define_Siv3D.h"

#include "Sequence.h"
#include "Compend.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class TxBs;
	using P_TxBs = std::shared_ptr < TxBs >;
	using VP_TxBs = std::vector < P_TxBs >;
	using PVP_TxBs = std::shared_ptr < VP_TxBs >;

	//================================================================
	//	イメージリストとシークエンスリスト
	//================================================================
	class Behavior : public Compend
	{
		PVP_TxBs	m_pvpTxBs;		//イメージ配列
//		PAP_Tx		m_pvpTx;		//イメージ配列
		PVP_Sqc		m_seq;			//シークエンス配列

	public:
		Behavior ();
		Behavior ( const Behavior & rhs ) = delete;
		~Behavior ();
	};

	using P_Behavior = std::shared_ptr < Behavior >;


}	//namespace GAME


