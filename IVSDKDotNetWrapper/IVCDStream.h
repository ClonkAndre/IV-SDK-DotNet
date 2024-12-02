#pragma once

namespace IVSDKDotNet
{
	public ref class IVCDStream
	{
	public:
		/// <summary>
		/// Adds a img file to the game.
		/// </summary>
		/// <param name="sPath">The path to the image file to add.</param>
		/// <param name="unk1">Unknown.</param>
		/// <param name="unkNeg1">Unknown.</param>
		/// <returns>The index at which the image was added in the cdimages array.</returns>
		static int AddImage(String^ sPath, uint8_t unk1, int32_t unkNeg1);

		/// <summary>
		/// Closes a single .img file making it so the game no longer blocks the file from being modified.
		/// <para>Closing a file and then trying to access it in-game will cause a crash.</para>
		/// </summary>
		/// <param name="index">The index of the image file in the cdimages array.</param>
		/// <returns>Not quite sure.</returns>
		static int CloseImageFile(int index);
		/// <summary>
		/// Closes all added .img files.
		/// </summary>
		/// <returns>Not quite sure.</returns>
		static int CloseAllImages();

		/// <summary>
		/// Gets the name of an added .img file.
		/// </summary>
		/// <param name="index">The index of the image file in the cdimages array.</param>
		/// <returns>The name of the .img file. Otherwise an empty string if the name couldn't be retrieved.</returns>
		static String^ GetImageFileName(int index);
		/// <summary>
		/// Gets the file handle of an added .img file.
		/// </summary>
		/// <param name="index">The index of the image file in the cdimages array.</param>
		/// <returns>The file handle of the .img file. Otherwise -1 if the file was being closed.</returns>
		static int GetImageFileHandle(int index);
	};
}