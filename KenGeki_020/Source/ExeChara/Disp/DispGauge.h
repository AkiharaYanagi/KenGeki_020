//=================================================================================================
//
// DispGauge ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//◆ 画像を用いたゲージ表示
	//　テクスチャは位置計算の基点が中心方向なので、２ｐ側のテクスチャを正とし１ｐ側は反転させる
	// 
	// [1P] ========= 99 ========= [2P]
	//				　↑	↑
	//

	class DispGauge : public TASK_VEC
	{
		PLAYER_ID	m_playerID {_PLAYER_NUM };		//プレイヤ表示側

		float		m_base_x { 0 };		//基準位置x
		float		m_base_y { 0 };		//基準位置y
		float		m_base_w { 0 };		//基準表示w
		float		m_base_h { 0 };		//基準表示h
		float		m_padding { 0 };	//パディング(端からの幅)

		int32		m_start { 10000 };	//初期値(基準)
		int32		m_base_max { 10000 };	//最大値(基準)
		UINT		m_value { 0 };		//値
		float		UNIT_LGS;			//1単位あたりの長さ
		float		m_dcr { 0 };		//減少分値

		//画像
		P_Grp		m_grp_Frame;	//枠
		P_Grp		m_grp_Value;	//値
		P_Grp		m_grp_Decrease;	//減少分(赤)	
		P_Grp		m_grp_White;	//回復分(白)	

		//減少分
		float		m_acc { 0.1f };	//加速度
		float		m_vel { 1.f };	//速度
		int			m_wait { 0 };	//待機時間
		bool		bStart { F };	//減少開始
		bool		bWait { F };	//待機開始

	public:
		DispGauge ();
		DispGauge ( const DispGauge & rhs ) = delete;
		~DispGauge ();

		//ゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID id );

		//基準位置設定
		void SetPosition ( VEC2 xy, VEC2 wh ) { SetPosition ( xy.x, xy.y, wh.x, wh.y ); }
		void SetPosition ( float x, float y, float w, float h );
		void SetPadding ( float p ) { m_padding = p; }
		void SetBaseMax ( int32 base_max ) { m_base_max = base_max; }

		void SetZ ( float z );

		//テクスチャ指定
		void SetTextureName_Frame ( s3d::String textureName );
		void SetTextureName_Value ( s3d::String textureName );
		void SetTextureName_Decrease ( s3d::String textureName );
		void SetTextureName_White ( s3d::String textureName );

		//カラーの設定
		void SetColor_Frame ( _CLR c );
		void SetColor_Decrease ( _CLR c );
		void SetColor_Value ( _CLR c0, _CLR c1, _CLR c2, _CLR c3 );

		//初期化
		void Init ();

		//値の更新
		void Update ( UINT value );
		void UpdateWhite ( int white );

		//最大値変更(値のみ、内部数値はBrlParamで制限)
		// 初期値 GAUGE_WIDTH ("FtgConst.h") のパーセントで変更 (0%~100%)
		void ChangeMax ( float percent );


		//全体表示切替
		void On ();
		void Off ();

		//減少分表示
		void OffDecrease () { m_grp_Decrease->SetValid ( F ); }

		//白ゲージ切替
		void OnWhite () { m_grp_White->SetValid ( T ); }
		void OffWhite () { m_grp_White->SetValid ( F ); }

		//画像切替
//		void GrpOn ();
//		void GrpOff ();

	private:
#pragma region CONST

		static const float LIFE_Y_REV;	//ライフゲージ補正
		static const float LIFE_H_REV;	//ライフゲージ補正

		static const float Z_GAUGE_FRAME;		//ライフゲージ表示前後・枠
		static const float Z_GAUGE_DECREASE;	//ライフゲージ表示前後・減少分
		static const float Z_GAUGE_WHITE;		//ライフゲージ表示前後・白
		static const float Z_GAUGE_VALUE;		//ライフゲージ表示前後・値
#pragma endregion

		void UpdateDecrease ();
	};

	using P_DispGauge = std::shared_ptr < DispGauge >;


}	//namespace GAME

