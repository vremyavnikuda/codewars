namespace CarManagementApp
{
    partial class CarEditForm
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.Label lblBrand;
        private System.Windows.Forms.TextBox txtBrand;
        private System.Windows.Forms.Label lblModel;
        private System.Windows.Forms.TextBox txtModel;
        private System.Windows.Forms.Label lblYear;
        private System.Windows.Forms.NumericUpDown numYear;
        private System.Windows.Forms.Label lblPower;
        private System.Windows.Forms.NumericUpDown numPower;
        private System.Windows.Forms.Label lblCost;
        private System.Windows.Forms.NumericUpDown numCost;
        private System.Windows.Forms.Button btnSave;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
                components.Dispose();
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            this.lblBrand = new System.Windows.Forms.Label();
            this.txtBrand = new System.Windows.Forms.TextBox();
            this.lblModel = new System.Windows.Forms.Label();
            this.txtModel = new System.Windows.Forms.TextBox();
            this.lblYear = new System.Windows.Forms.Label();
            this.numYear = new System.Windows.Forms.NumericUpDown();
            this.lblPower = new System.Windows.Forms.Label();
            this.numPower = new System.Windows.Forms.NumericUpDown();
            this.lblCost = new System.Windows.Forms.Label();
            this.numCost = new System.Windows.Forms.NumericUpDown();
            this.btnSave = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numYear)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCost)).BeginInit();
            this.SuspendLayout();
            // 
            // lblBrand
            // 
            this.lblBrand.Location = new System.Drawing.Point(12, 15);
            this.lblBrand.Name = "lblBrand";
            this.lblBrand.Size = new System.Drawing.Size(80, 23);
            this.lblBrand.Text = "Марка:";
            // 
            // txtBrand
            // 
            this.txtBrand.Location = new System.Drawing.Point(98, 12);
            this.txtBrand.Name = "txtBrand";
            this.txtBrand.Size = new System.Drawing.Size(200, 20);
            // 
            // lblModel
            // 
            this.lblModel.Location = new System.Drawing.Point(12, 45);
            this.lblModel.Name = "lblModel";
            this.lblModel.Size = new System.Drawing.Size(80, 23);
            this.lblModel.Text = "Модель:";
            // 
            // txtModel
            // 
            this.txtModel.Location = new System.Drawing.Point(98, 42);
            this.txtModel.Name = "txtModel";
            this.txtModel.Size = new System.Drawing.Size(200, 20);
            // 
            // lblYear
            // 
            this.lblYear.Location = new System.Drawing.Point(12, 75);
            this.lblYear.Name = "lblYear";
            this.lblYear.Size = new System.Drawing.Size(80, 23);
            this.lblYear.Text = "Год выпуска:";
            // 
            // numYear
            // 
            this.numYear.Location = new System.Drawing.Point(98, 73);
            this.numYear.Minimum = new decimal(new int[] { 1900, 0, 0, 0 });
            this.numYear.Maximum = new decimal(new int[] { DateTime.Now.Year, 0, 0, 0 });
            this.numYear.Name = "numYear";
            this.numYear.Size = new System.Drawing.Size(200, 20);
            this.numYear.Value = new decimal(new int[] { DateTime.Now.Year, 0, 0, 0 });
            // 
            // lblPower
            // 
            this.lblPower.Location = new System.Drawing.Point(12, 105);
            this.lblPower.Name = "lblPower";
            this.lblPower.Size = new System.Drawing.Size(80, 23);
            this.lblPower.Text = "Мощность:";
            // 
            // numPower
            // 
            this.numPower.Location = new System.Drawing.Point(98, 103);
            this.numPower.Maximum = new decimal(new int[] { 1000, 0, 0, 0 });
            this.numPower.Name = "numPower";
            this.numPower.Size = new System.Drawing.Size(200, 20);
            // 
            // lblCost
            // 
            this.lblCost.Location = new System.Drawing.Point(12, 135);
            this.lblCost.Name = "lblCost";
            this.lblCost.Size = new System.Drawing.Size(80, 23);
            this.lblCost.Text = "Стоимость:";
            // 
            // numCost
            // 
            this.numCost.Location = new System.Drawing.Point(98, 133);
            this.numCost.Maximum = new decimal(new int[] { 10000000, 0, 0, 0 });
            this.numCost.Name = "numCost";
            this.numCost.Size = new System.Drawing.Size(200, 20);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(98, 170);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(100, 30);
            this.btnSave.Text = "Сохранить";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // CarEditForm
            // 
            this.ClientSize = new System.Drawing.Size(320, 220);
            this.Controls.Add(this.lblBrand);
            this.Controls.Add(this.txtBrand);
            this.Controls.Add(this.lblModel);
            this.Controls.Add(this.txtModel);
            this.Controls.Add(this.lblYear);
            this.Controls.Add(this.numYear);
            this.Controls.Add(this.lblPower);
            this.Controls.Add(this.numPower);
            this.Controls.Add(this.lblCost);
            this.Controls.Add(this.numCost);
            this.Controls.Add(this.btnSave);
            this.Name = "CarEditForm";
            this.Text = "Редактирование автомобиля";
            ((System.ComponentModel.ISupportInitialize)(this.numYear)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCost)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
    }
}
