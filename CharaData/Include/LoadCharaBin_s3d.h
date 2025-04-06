//=================================================================================================
//
// LoadCharaBin_s3d ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "LoadCharaBinFunc_s3d.h"
#include "LoadCharaBinFunc.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------
	// .datファイルからCharaを読み込む
	//------------------------------------------------------
	class LoadCharaBin_s3d
	{
		LoadCharaBinFunc		m_func;

	public:
//		LoadCharaBin_s3d ( const s3d::String & filename,  Chara & chara );
//		LoadCharaBin_s3d ( const LoadCharaBin_s3d& rhs ) = delete;
		LoadCharaBin_s3d ();
		~LoadCharaBin_s3d ();

		void Load ( const s3d::String & filename,  Chara & chara );

	private:
		//try用

		//.dat
		void _Load ( const s3d::String & filename,  Chara & chara );

		//.scp
		void _Load_scp ( const s3d::String & filename,  Chara & chara );


	};


}	//namespace GAME


