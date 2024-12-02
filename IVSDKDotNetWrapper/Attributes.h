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
		public ref class SpeedAttribute : Attribute
		{
		public:
			float Speed;

		public:
			SpeedAttribute(float speed)
			{
				Speed = speed;
			}
		};

		[AttributeUsageAttribute(AttributeTargets::Field)]
		public ref class RangeAttribute : Attribute
		{
		public:
			float Minimum;
			float Maximum;

		public:
			RangeAttribute(float min, float max)
			{
				Minimum = min;
				Maximum = max;
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