//=================================================================================================
//
// LoadImgFile ヘッダファイル
//
//=================================================================================================
#pragma once
#include "Define.h"
#include "Document.h"
#include <filesystem>

#include "IOCharaDefine.h"

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
		PAP_Tx LoadImg ();
		PAP_Tx LoadAtlas();
	};


}	//namespace GAME


