namespace APITest
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.testButton = new System.Windows.Forms.Button();
            this.testButton2 = new System.Windows.Forms.Button();
            this.ReloadScriptsButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.connectButton = new System.Windows.Forms.Button();
            this.disconnectButton = new System.Windows.Forms.Button();
            this.logLB = new System.Windows.Forms.ListBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.getSessionInfoButton = new System.Windows.Forms.Button();
            this.getPlayerNameNativeButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.getActiveScriptsCountButton = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.scriptNameTextbox = new System.Windows.Forms.TextBox();
            this.getRunningScriptsButton = new System.Windows.Forms.Button();
            this.loadScriptButton = new System.Windows.Forms.Button();
            this.abortScriptsButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // testButton
            // 
            this.testButton.ForeColor = System.Drawing.Color.Black;
            this.testButton.Location = new System.Drawing.Point(200, 25);
            this.testButton.Name = "testButton";
            this.testButton.Size = new System.Drawing.Size(75, 23);
            this.testButton.TabIndex = 0;
            this.testButton.Text = "Test1";
            this.testButton.UseVisualStyleBackColor = true;
            this.testButton.Click += new System.EventHandler(this.testButton_Click);
            // 
            // testButton2
            // 
            this.testButton2.ForeColor = System.Drawing.Color.Black;
            this.testButton2.Location = new System.Drawing.Point(281, 25);
            this.testButton2.Name = "testButton2";
            this.testButton2.Size = new System.Drawing.Size(75, 23);
            this.testButton2.TabIndex = 1;
            this.testButton2.Text = "Test2";
            this.testButton2.UseVisualStyleBackColor = true;
            this.testButton2.Click += new System.EventHandler(this.testButton2_Click);
            // 
            // ReloadScriptsButton
            // 
            this.ReloadScriptsButton.ForeColor = System.Drawing.Color.Black;
            this.ReloadScriptsButton.Location = new System.Drawing.Point(12, 67);
            this.ReloadScriptsButton.Name = "ReloadScriptsButton";
            this.ReloadScriptsButton.Size = new System.Drawing.Size(91, 23);
            this.ReloadScriptsButton.TabIndex = 2;
            this.ReloadScriptsButton.Text = "ReloadScripts";
            this.ReloadScriptsButton.UseVisualStyleBackColor = true;
            this.ReloadScriptsButton.Click += new System.EventHandler(this.ReloadScriptsButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Manager";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Connection";
            // 
            // connectButton
            // 
            this.connectButton.ForeColor = System.Drawing.Color.Black;
            this.connectButton.Location = new System.Drawing.Point(12, 25);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(88, 23);
            this.connectButton.TabIndex = 5;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // disconnectButton
            // 
            this.disconnectButton.ForeColor = System.Drawing.Color.Black;
            this.disconnectButton.Location = new System.Drawing.Point(106, 25);
            this.disconnectButton.Name = "disconnectButton";
            this.disconnectButton.Size = new System.Drawing.Size(88, 23);
            this.disconnectButton.TabIndex = 6;
            this.disconnectButton.Text = "Disconnect";
            this.disconnectButton.UseVisualStyleBackColor = true;
            this.disconnectButton.Click += new System.EventHandler(this.disconnectButton_Click);
            // 
            // logLB
            // 
            this.logLB.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.logLB.BackColor = System.Drawing.Color.Gray;
            this.logLB.FormattingEnabled = true;
            this.logLB.Location = new System.Drawing.Point(12, 261);
            this.logLB.Name = "logLB";
            this.logLB.Size = new System.Drawing.Size(682, 160);
            this.logLB.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 245);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(25, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Log";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 131);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Game";
            // 
            // getSessionInfoButton
            // 
            this.getSessionInfoButton.ForeColor = System.Drawing.Color.Black;
            this.getSessionInfoButton.Location = new System.Drawing.Point(12, 147);
            this.getSessionInfoButton.Name = "getSessionInfoButton";
            this.getSessionInfoButton.Size = new System.Drawing.Size(91, 23);
            this.getSessionInfoButton.TabIndex = 10;
            this.getSessionInfoButton.Text = "GetSessionInfo";
            this.getSessionInfoButton.UseVisualStyleBackColor = true;
            this.getSessionInfoButton.Click += new System.EventHandler(this.getSessionInfoButton_Click);
            // 
            // getPlayerNameNativeButton
            // 
            this.getPlayerNameNativeButton.ForeColor = System.Drawing.Color.Black;
            this.getPlayerNameNativeButton.Location = new System.Drawing.Point(109, 147);
            this.getPlayerNameNativeButton.Name = "getPlayerNameNativeButton";
            this.getPlayerNameNativeButton.Size = new System.Drawing.Size(183, 23);
            this.getPlayerNameNativeButton.TabIndex = 11;
            this.getPlayerNameNativeButton.Text = "Call GET_PLAYER_NAME Native";
            this.getPlayerNameNativeButton.UseVisualStyleBackColor = true;
            this.getPlayerNameNativeButton.Click += new System.EventHandler(this.getPlayerNameNativeButton_Click);
            // 
            // button1
            // 
            this.button1.ForeColor = System.Drawing.Color.Black;
            this.button1.Location = new System.Drawing.Point(298, 147);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(183, 23);
            this.button1.TabIndex = 12;
            this.button1.Text = "Call GET_CHAR_COORDINATES Native";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // getActiveScriptsCountButton
            // 
            this.getActiveScriptsCountButton.ForeColor = System.Drawing.Color.Black;
            this.getActiveScriptsCountButton.Location = new System.Drawing.Point(219, 67);
            this.getActiveScriptsCountButton.Name = "getActiveScriptsCountButton";
            this.getActiveScriptsCountButton.Size = new System.Drawing.Size(125, 23);
            this.getActiveScriptsCountButton.TabIndex = 13;
            this.getActiveScriptsCountButton.Text = "GetActiveScriptsCount";
            this.getActiveScriptsCountButton.UseVisualStyleBackColor = true;
            this.getActiveScriptsCountButton.Click += new System.EventHandler(this.getActiveScriptsCountButton_Click);
            // 
            // button2
            // 
            this.button2.ForeColor = System.Drawing.Color.Black;
            this.button2.Location = new System.Drawing.Point(12, 96);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(91, 23);
            this.button2.TabIndex = 14;
            this.button2.Text = "IsScriptRunning";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // scriptNameTextbox
            // 
            this.scriptNameTextbox.Location = new System.Drawing.Point(303, 98);
            this.scriptNameTextbox.Name = "scriptNameTextbox";
            this.scriptNameTextbox.Size = new System.Drawing.Size(138, 20);
            this.scriptNameTextbox.TabIndex = 15;
            // 
            // getRunningScriptsButton
            // 
            this.getRunningScriptsButton.ForeColor = System.Drawing.Color.Black;
            this.getRunningScriptsButton.Location = new System.Drawing.Point(109, 67);
            this.getRunningScriptsButton.Name = "getRunningScriptsButton";
            this.getRunningScriptsButton.Size = new System.Drawing.Size(104, 23);
            this.getRunningScriptsButton.TabIndex = 16;
            this.getRunningScriptsButton.Text = "GetRunningScripts";
            this.getRunningScriptsButton.UseVisualStyleBackColor = true;
            this.getRunningScriptsButton.Click += new System.EventHandler(this.getRunningScriptsButton_Click);
            // 
            // loadScriptButton
            // 
            this.loadScriptButton.ForeColor = System.Drawing.Color.Black;
            this.loadScriptButton.Location = new System.Drawing.Point(109, 96);
            this.loadScriptButton.Name = "loadScriptButton";
            this.loadScriptButton.Size = new System.Drawing.Size(91, 23);
            this.loadScriptButton.TabIndex = 17;
            this.loadScriptButton.Text = "LoadScript";
            this.loadScriptButton.UseVisualStyleBackColor = true;
            this.loadScriptButton.Click += new System.EventHandler(this.loadScriptButton_Click);
            // 
            // abortScriptsButton
            // 
            this.abortScriptsButton.ForeColor = System.Drawing.Color.Black;
            this.abortScriptsButton.Location = new System.Drawing.Point(206, 96);
            this.abortScriptsButton.Name = "abortScriptsButton";
            this.abortScriptsButton.Size = new System.Drawing.Size(91, 23);
            this.abortScriptsButton.TabIndex = 18;
            this.abortScriptsButton.Text = "AbortScript";
            this.abortScriptsButton.UseVisualStyleBackColor = true;
            this.abortScriptsButton.Click += new System.EventHandler(this.abortScriptsButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(706, 433);
            this.Controls.Add(this.abortScriptsButton);
            this.Controls.Add(this.loadScriptButton);
            this.Controls.Add(this.getRunningScriptsButton);
            this.Controls.Add(this.scriptNameTextbox);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.getActiveScriptsCountButton);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.getPlayerNameNativeButton);
            this.Controls.Add(this.getSessionInfoButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.logLB);
            this.Controls.Add(this.disconnectButton);
            this.Controls.Add(this.connectButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ReloadScriptsButton);
            this.Controls.Add(this.testButton2);
            this.Controls.Add(this.testButton);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "IV-SDK .NET API Test";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button testButton;
        private System.Windows.Forms.Button testButton2;
        private System.Windows.Forms.Button ReloadScriptsButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.Button disconnectButton;
        private System.Windows.Forms.ListBox logLB;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button getSessionInfoButton;
        private System.Windows.Forms.Button getPlayerNameNativeButton;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button getActiveScriptsCountButton;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox scriptNameTextbox;
        private System.Windows.Forms.Button getRunningScriptsButton;
        private System.Windows.Forms.Button loadScriptButton;
        private System.Windows.Forms.Button abortScriptsButton;
    }
}

