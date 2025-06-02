using System;
using System.Numerics;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

namespace Manager.Classes
{
    public class ImPopup
    {

        #region Variables
        private string title;
        private string description;
        private Vector2 windowSize;
        private bool autoResizeWindow;
        private bool centerInMiddleOfScreen;
        private string buttonOneText;
        private string buttonTwoText;
        private Action buttonOneAction;
        private Action buttonTwoAction;
        #endregion

        #region Constructor
        public ImPopup(string title, string desc, Vector2 size, bool centerInMiddleOfScreen, string btnOneText, string btnTwoText, Action btnOneAct, Action btnTwoAct)
        {
            this.title = title;
            description = desc;
            windowSize = size;
            autoResizeWindow = false;
            this.centerInMiddleOfScreen = centerInMiddleOfScreen;
            buttonOneText = btnOneText;
            buttonTwoText = btnTwoText;
            buttonOneAction = btnOneAct;
            buttonTwoAction = btnTwoAct;
        }
        public ImPopup(string title, string desc, bool centerInMiddleOfScreen, string btnOneText, string btnTwoText, Action btnOneAct, Action btnTwoAct)
        {
            this.title = title;
            description = desc;
            autoResizeWindow = true;
            this.centerInMiddleOfScreen = centerInMiddleOfScreen;
            buttonOneText = btnOneText;
            buttonTwoText = btnTwoText;
            buttonOneAction = btnOneAct;
            buttonTwoAction = btnTwoAct;
        }
        #endregion

        public void Open()
        {
            ImGuiIV.OpenPopup(title);
        }

        /// <summary>
        /// Displays the popup dialog.
        /// </summary>
        /// <returns><see langword="true"/> if the popup dialog is open and visible. <see langword="false"/> if the dialog is closed and can be removed.</returns>
        public bool Show()
        {
            bool result = ImGuiIV.CreateSimplePopupDialog(title,
                description,
                autoResizeWindow ? Vector2.Zero : windowSize,
                autoResizeWindow ? eImGuiWindowFlags.AlwaysAutoResize : eImGuiWindowFlags.None,
                centerInMiddleOfScreen,
                buttonOneText != null,
                buttonTwoText != null,
                buttonOneText,
                buttonTwoText,
                buttonOneAction,
                buttonTwoAction);

            return result;
        }

    }
}
