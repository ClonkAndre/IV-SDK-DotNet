#pragma once
#include "pch.h"

namespace IVSDKDotNet
{
	namespace Attributes
	{

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class SeparatorAttribute : Attribute
		{
		public:
			String^ Text;

		public:
			SeparatorAttribute(String^ text)
			{
				Text = text;
			}
			SeparatorAttribute()
			{
				Text = String::Empty;
			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class SpaceAttribute : Attribute
		{
		public:
			float Height;

		public:
			SpaceAttribute(float height)
			{
				Height = height;
			}
			SpaceAttribute()
			{
				Height = 0.0F;
			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class HelpMarkerAttribute : Attribute
		{
		public:
			String^ Text;

		public:
			HelpMarkerAttribute(String^ text)
			{
				Text = text;
			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class HideInInspectorAttribute : Attribute
		{
		public:
			HideInInspectorAttribute()
			{

			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class ReadOnlyInInspectorAttribute : Attribute
		{
		public:
			ReadOnlyInInspectorAttribute()
			{

			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class ExcludeFromJsonSerializationAttribute : Attribute
		{
		public:
			ExcludeFromJsonSerializationAttribute()
			{

			}
		};

		[AttributeUsageAttribute(AttributeTargets::Class)]
		public ref class ShowStaticFieldsInInspector : Attribute
		{
		public:
			ShowStaticFieldsInInspector()
			{
				
			}
		};

	}
}