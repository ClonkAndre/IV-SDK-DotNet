using System.Collections.Generic;
using System.Reflection;

using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Manager.Classes.Json
{
    internal class JsonHelper
    {

        public class IgnorePropertiesResolver : DefaultContractResolver
        {

            #region Variables
            private readonly HashSet<string> ignoreProps;
            #endregion

            #region Constructor
            public IgnorePropertiesResolver(IEnumerable<string> propNamesToIgnore)
            {
                ignoreProps = new HashSet<string>(propNamesToIgnore);
            }
            #endregion

            protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
            {
                JsonProperty property = base.CreateProperty(member, memberSerialization);
                if (ignoreProps.Contains(property.PropertyName))
                {
                    property.ShouldSerialize = _ => false;
                }
                return property;
            }

        }

    }
}
