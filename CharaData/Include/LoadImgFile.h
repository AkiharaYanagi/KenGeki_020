//=================================================================================================
//
// LoadImgFile ヘッダファイル
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Define.h"
#include "Define_Siv3D.h"
#include "04_GameFile.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//.imgファイルからPAP_TXを得る
	class LoadImgFile
	{
	public:
		PAP_Tx Do ( s3d::String filepath );

		void Conversion ( s3d::String filepath );
		PAP_Tx LoadTx ();

		//Img->PAP_Tx
		PAP_Tx LoadImg ();

		//Atlas -> PAP_Tx
		PAP_Tx LoadAtlas( s3d::String filepath );

		//LZ4 -> PAP_Tx
		PAP_Tx LoadLz4 ( s3d::String filepath );
		PAP_Tx LoadLz4_Bhv ( s3d::String filepath );
		PAP_Tx LoadLz4_Bhv_Name ( s3d::String filepath );
		PAP_Tx LoadLz4_Gns ( s3d::String filepath );
		PAP_Tx LoadLz4_Gns_Name ( s3d::String filepath );
	};


}	//namespace GAME


