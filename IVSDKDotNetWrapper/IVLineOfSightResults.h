#pragma once

namespace IVSDKDotNet
{
	public value struct IVLineOfSightResults
	{
	public:
		/// <summary>
		/// IVPhInstGta pointer of hit entity.
		/// Use with: IVPhInstGta.FromPointer(...);
		/// </summary>
		property UIntPtr Inst
		{
		public:
			UIntPtr get()
			{
				if (!m_bValid)
					return UIntPtr::Zero;

				return m_pInst;
			}
		private:
			void set(UIntPtr value)
			{
				m_pInst = value;
			}
		}
		/// <summary>
		/// Where the line of sight hit point ended up.
		/// </summary>
		property Vector3 EndPosition
		{
		public:
			Vector3 get()
			{
				if (!m_bValid)
					return Vector3::Zero;

				return m_vEndPosition;
			}
		private:
			void set(Vector3 value)
			{
				m_vEndPosition = value;
			}
		}
		property uint32_t UnkFlags
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags = value;
			}
		}
		property Vector3 Unk
		{
		public:
			Vector3 get()
			{
				if (!m_bValid)
					return Vector3::Zero;

				return m_vUnk;
			}
		private:
			void set(Vector3 value)
			{
				m_vUnk = value;
			}
		}
		property uint32_t UnkFlags2
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags2;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags2 = value;
			}
		}
		property Vector3 Unk2
		{
		public:
			Vector3 get()
			{
				if (!m_bValid)
					return Vector3::Zero;

				return m_vUnk2;
			}
		private:
			void set(Vector3 value)
			{
				m_vUnk2 = value;
			}
		}
		property uint32_t UnkFlags3
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags3;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags3 = value;
			}
		}
		property float UnkFloat1
		{
		public:
			float get()
			{
				if (!m_bValid)
					return 0.0F;

				return m_fUnk1;
			}
		private:
			void set(float value)
			{
				m_fUnk1 = value;
			}
		}
		property float UnkFloat2
		{
		public:
			float get()
			{
				if (!m_bValid)
					return 0.0F;

				return m_fUnk2;
			}
		private:
			void set(float value)
			{
				m_fUnk2 = value;
			}
		}
		property uint32_t UnkFlags4
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags4;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags4 = value;
			}
		}
		property uint32_t UnkFlags5
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags5;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags5 = value;
			}
		}
		property uint32_t UnkFlags6
		{
		public:
			uint32_t get()
			{
				if (!m_bValid)
					return 0;

				return m_nUnkFlags6;
			}
		private:
			void set(uint32_t value)
			{
				m_nUnkFlags6 = value;
			}
		}

	internal:
		IVLineOfSightResults(tLineOfSightResults* nativePtr);

		static IVLineOfSightResults Empty();

	internal:
		bool m_bValid;

		UIntPtr m_pInst;
		Vector3 m_vEndPosition;
		uint32_t m_nUnkFlags;
		Vector3 m_vUnk;
		uint32_t m_nUnkFlags2;
		Vector3 m_vUnk2;
		uint32_t m_nUnkFlags3;
		float m_fUnk1;
		float m_fUnk2;
		uint32_t m_nUnkFlags4;
		uint32_t m_nUnkFlags5;
		uint32_t m_nUnkFlags6;

	};
}