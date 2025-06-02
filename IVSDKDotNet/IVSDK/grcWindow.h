namespace rage
{
	class grcWindow
	{
	public:
		static bool ProcessWindowMessage()
		{
			return ((bool(__cdecl*)())(AddressSetter::Get("grcWindow", "ProcessWindowMessage")))();
		}
	};
}