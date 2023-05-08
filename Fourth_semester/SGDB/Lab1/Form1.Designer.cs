namespace Project1_SGBD
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
            Label labelPret;
            buttonConnect = new Button();
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            buttonDelete = new Button();
            buttonAdd = new Button();
            textBoxCantitate = new TextBox();
            textBoxDenumire = new TextBox();
            textBoxPret = new TextBox();
            textBoxDescriere = new TextBox();
            labelCantitate = new Label();
            labelDenumire = new Label();
            labelDescriere = new Label();
            buttonUpdate = new Button();
            labelPret = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // labelPret
            // 
            labelPret.AutoSize = true;
            labelPret.Location = new Point(501, 7);
            labelPret.Name = "labelPret";
            labelPret.Size = new Size(35, 20);
            labelPret.TabIndex = 14;
            labelPret.Text = "Pret";
            // 
            // buttonConnect
            // 
            buttonConnect.BackColor = Color.WhiteSmoke;
            buttonConnect.Location = new Point(434, 632);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(149, 61);
            buttonConnect.TabIndex = 1;
            buttonConnect.Text = "Connect to DB";
            buttonConnect.UseVisualStyleBackColor = false;
            buttonConnect.Click += buttonConnect_Click;
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.AllowUserToAddRows = false;
            dataGridViewParent.AllowUserToDeleteRows = false;
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(28, 140);
            dataGridViewParent.MultiSelect = false;
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.ReadOnly = true;
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.RowTemplate.Height = 29;
            dataGridViewParent.Size = new Size(466, 470);
            dataGridViewParent.TabIndex = 5;
            dataGridViewParent.CellClick += dataGridViewParent_CellClick;
            dataGridViewParent.CellContentClick += dataGridViewParent_CellClick;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.AllowUserToAddRows = false;
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(511, 140);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.ReadOnly = true;
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.RowTemplate.Height = 29;
            dataGridViewChild.Size = new Size(468, 470);
            dataGridViewChild.TabIndex = 6;
            dataGridViewChild.CellClick += dataGridViewChild_CellEndEdit;
            dataGridViewChild.CellContentClick += dataGridViewChild_CellEndEdit;
            dataGridViewChild.CellEndEdit += dataGridViewChild_CellEndEdit;
            // 
            // buttonDelete
            // 
            buttonDelete.BackColor = Color.WhiteSmoke;
            buttonDelete.Location = new Point(430, 78);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(138, 43);
            buttonDelete.TabIndex = 7;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = false;
            buttonDelete.Click += buttonDelete_Click;
            // 
            // buttonAdd
            // 
            buttonAdd.BackColor = Color.WhiteSmoke;
            buttonAdd.Location = new Point(275, 78);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(138, 43);
            buttonAdd.TabIndex = 7;
            buttonAdd.Text = "Add";
            buttonAdd.UseVisualStyleBackColor = false;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // textBoxCantitate
            // 
            textBoxCantitate.Location = new Point(214, 30);
            textBoxCantitate.Name = "textBoxCantitate";
            textBoxCantitate.Size = new Size(125, 27);
            textBoxCantitate.TabIndex = 8;
            // 
            // textBoxDenumire
            // 
            textBoxDenumire.Location = new Point(359, 30);
            textBoxDenumire.Name = "textBoxDenumire";
            textBoxDenumire.Size = new Size(125, 27);
            textBoxDenumire.TabIndex = 9;
            // 
            // textBoxPret
            // 
            textBoxPret.Location = new Point(501, 30);
            textBoxPret.Name = "textBoxPret";
            textBoxPret.Size = new Size(125, 27);
            textBoxPret.TabIndex = 10;
            // 
            // textBoxDescriere
            // 
            textBoxDescriere.Location = new Point(642, 30);
            textBoxDescriere.Name = "textBoxDescriere";
            textBoxDescriere.Size = new Size(125, 27);
            textBoxDescriere.TabIndex = 11;
            // 
            // labelCantitate
            // 
            labelCantitate.AutoSize = true;
            labelCantitate.Location = new Point(214, 7);
            labelCantitate.Name = "labelCantitate";
            labelCantitate.Size = new Size(69, 20);
            labelCantitate.TabIndex = 12;
            labelCantitate.Text = "Cantitate";
            // 
            // labelDenumire
            // 
            labelDenumire.AutoSize = true;
            labelDenumire.Location = new Point(359, 7);
            labelDenumire.Name = "labelDenumire";
            labelDenumire.Size = new Size(74, 20);
            labelDenumire.TabIndex = 13;
            labelDenumire.Text = "Denumire";
            // 
            // labelDescriere
            // 
            labelDescriere.AutoSize = true;
            labelDescriere.Location = new Point(642, 7);
            labelDescriere.Name = "labelDescriere";
            labelDescriere.Size = new Size(71, 20);
            labelDescriere.TabIndex = 15;
            labelDescriere.Text = "Descriere";
            // 
            // buttonUpdate
            // 
            buttonUpdate.BackColor = Color.WhiteSmoke;
            buttonUpdate.Location = new Point(583, 78);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(138, 43);
            buttonUpdate.TabIndex = 16;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = false;
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.MediumTurquoise;
            ClientSize = new Size(1012, 698);
            Controls.Add(buttonUpdate);
            Controls.Add(labelDescriere);
            Controls.Add(labelPret);
            Controls.Add(labelDenumire);
            Controls.Add(labelCantitate);
            Controls.Add(textBoxDescriere);
            Controls.Add(textBoxPret);
            Controls.Add(textBoxDenumire);
            Controls.Add(textBoxCantitate);
            Controls.Add(buttonAdd);
            Controls.Add(buttonDelete);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Controls.Add(buttonConnect);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private Button buttonConnect;
        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewChild;
        private Button buttonDelete;
        private Button buttonAdd;
        private TextBox textBoxCantitate;
        private TextBox textBoxDenumire;
        private TextBox textBoxPret;
        private TextBox textBoxDescriere;
        private Label labelCantitate;
        private Label labelDenumire;
        private Label labelDescriere;
        private Button buttonUpdate;
    }
}