//=================================================================================================
//
//	EfPart ヘッダファイル
//		打合時に発生するの回収可能な粒子
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//パラメータ
	struct PrmEfPart
	{
		P_Ob	m_pOb;
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_gotten;		//重なり取得フラグ

		UINT	m_count;		//開始カウント

	public:
		PrmEfPart ()
			: m_pOb ( nullptr )
			, m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_gotten ( F )
			, m_count ( 0 )
		{}
	};

	//粒子エフェクトクラス
	class EfPart : public GameGraphic
	{
		enum NUM
		{
			SPARK_NUM = 30,		//1回発生個数
			SPARK_MAX = 300,	//最大個数
			SPARK_INIT = 30,	//取得可能フレーム
		};
		std::vector < PrmEfPart >	mv_Prm;	//パラメータ
		std::vector < UINT >		mv_Rnd;	//非稼働オブジェクト数上

	public:
		EfPart ();
		EfPart ( const EfPart & rhs ) = delete;
		~EfPart ();
		
		//初期化
		void Init ();

		void Move ();
		void On ( VEC2 center );
		void Off ();


		std::vector < PrmEfPart > & Getrv_Prm () { return mv_Prm; }


		//重なり判定
		//戻値：重なり個数
		UINT Collision ( PV_RECT pv_rect );


	private:
		//引数のベクタに0からN-1までの乱数を格納する
		void Rnd_0_N ( UINT N, std::vector < UINT > & vec );
	};

	using P_EfPart = std::shared_ptr < EfPart >;

}	//namespace GAME


