namespace Lab2_SGBD
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            dataGridViewChild = new DataGridView();
            dataGridViewParent = new DataGridView();
            buttonConnect = new Button();
            buttonUpdate = new Button();
            buttonAdd = new Button();
            buttonDelete = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.AllowUserToAddRows = false;
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(495, 149);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.ReadOnly = true;
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.RowTemplate.Height = 29;
            dataGridViewChild.Size = new Size(468, 470);
            dataGridViewChild.TabIndex = 9;
            dataGridViewChild.CellClick += dataGridViewChild_CellEndEdit;
            dataGridViewChild.CellContentClick += dataGridViewChild_CellEndEdit;
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.AllowUserToAddRows = false;
            dataGridViewParent.AllowUserToDeleteRows = false;
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(12, 149);
            dataGridViewParent.MultiSelect = false;
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.ReadOnly = true;
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.RowTemplate.Height = 29;
            dataGridViewParent.Size = new Size(466, 470);
            dataGridViewParent.TabIndex = 8;
            dataGridViewParent.CellClick += dataGridViewParent_CellClick;
            dataGridViewParent.CellContentClick += dataGridViewParent_CellClick;
            // 
            // buttonConnect
            // 
            buttonConnect.BackColor = Color.WhiteSmoke;
            buttonConnect.Location = new Point(415, 630);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(149, 61);
            buttonConnect.TabIndex = 7;
            buttonConnect.Text = "Connect to DB";
            buttonConnect.UseVisualStyleBackColor = false;
            buttonConnect.Click += buttonConnect_Click;
            // 
            // buttonUpdate
            // 
            buttonUpdate.BackColor = Color.WhiteSmoke;
            buttonUpdate.Location = new Point(579, 90);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(138, 43);
            buttonUpdate.TabIndex = 19;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = false;
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // buttonAdd
            // 
            buttonAdd.BackColor = Color.WhiteSmoke;
            buttonAdd.Location = new Point(271, 90);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(138, 43);
            buttonAdd.TabIndex = 17;
            buttonAdd.Text = "Add";
            buttonAdd.UseVisualStyleBackColor = false;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // buttonDelete
            // 
            buttonDelete.BackColor = Color.WhiteSmoke;
            buttonDelete.Location = new Point(426, 90);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(138, 43);
            buttonDelete.TabIndex = 18;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = false;
            buttonDelete.Click += buttonDelete_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.FromArgb(0, 192, 192);
            ClientSize = new Size(988, 699);
            Controls.Add(buttonUpdate);
            Controls.Add(buttonAdd);
            Controls.Add(buttonDelete);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Controls.Add(buttonConnect);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridViewChild;
        private DataGridView dataGridViewParent;
        private Button buttonConnect;
        private Button buttonUpdate;
        private Button buttonAdd;
        private Button buttonDelete;
    }
}