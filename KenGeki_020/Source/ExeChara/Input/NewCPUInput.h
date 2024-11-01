//=================================================================================================
//
// NewCPUInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class NewCPUInput : public CharaInput
	{
		//重み定数
		static const std::vector < double > weights;

		//重み付き確率
		std::discrete_distribution <>	m_dist;

		//ランダムデバイス
		std::random_device	m_rnd_dev;

		//メルセンヌ・ツイスタ
		std::mt19937 m_gen;


		//キー
		//重み定数
		static const std::vector < double > weights_key;

		//重み付き確率
		std::discrete_distribution <>	m_dist_key;


	public:
		NewCPUInput ();
		NewCPUInput ( const NewCPUInput & rhs ) = delete;
		~NewCPUInput ();

		void Load ();
		void Update ( bool dirRight );
	};

	using P_NewCPUInput = std::shared_ptr < NewCPUInput >;


}	//namespace GAME


