//=================================================================================================
//
//	ScriptParam_Staging ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	struct ScriptParam_Staging
	{
	public:
		//演出(全体)
		UINT	BlackOut { 0 };		//暗転[F]
		UINT	Vibration { 0 };	//振動[F](全体)
		UINT	Stop { 0 };			//停止[F](全体)

		//------
		//演出(個別)
		int		Rotate { 0 };				//回転[rad] ( 0->2π, π/100 )
		VEC2	Rotate_center { 0, 0 };		//回転中心(x,y)
		UINT	AfterImage_N { 0 };			//残像[個]
		UINT	AfterImage_time { 0 };		//残像[F] 持続
		UINT	AfterImage_pitch { 0 };		//残像[F] pitch
		UINT	Vibration_S { 0 };			//振動[F](個別)
		_CLR	Color { 0xffffffff };		//色調変更
		UINT	Color_time { 0 };			//色調変更[F] 持続

		//------
		VEC2	Scaling { 1.f, 1.f };	//拡大縮小
		UINT	SE { 0 };		//SEの指定
		s3d::String		SE_Name { U"" };		//SE名
		s3d::String		VC_Name { U"" };		//VC名

		//=======================================
		ScriptParam_Staging ();
		ScriptParam_Staging ( const ScriptParam_Staging & rhs ) = delete;
		~ScriptParam_Staging ();
		//=======================================

		//bool Shader { F };		//シェーダ利用(ID)
		//SE・EF、ガード時・ヒット時分岐
	};


}	//namespace GAME


