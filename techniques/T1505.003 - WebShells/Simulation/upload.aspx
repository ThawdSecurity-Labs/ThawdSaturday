<%@ Page Language="C#" AutoEventWireup="true" %>

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>File Uploader</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f4f4f9;
        }

        .container {
            max-width: 500px;
            margin: auto;
            padding: 20px;
            background: white;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }

        h1 {
            color: #333;
        }

        .file-upload input[type="file"] {
            margin: 10px 0;
        }

        .upload-btn {
            background-color: #4CAF50;
            color: white;
            padding: 10px 15px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        .upload-btn:hover {
            background-color: #45a049;
        }

        .message {
            margin-top: 15px;
            color: green;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="container">
            <h1>File Uploader</h1>
            <div class="file-upload">
                <asp:FileUpload ID="FileUploader" runat="server" />
                <br />
                <asp:Button ID="UploadButton" runat="server" Text="Upload File" CssClass="upload-btn" OnClick="UploadButton_Click" />
            </div>
            <div class="message">
                <asp:Label ID="MessageLabel" runat="server"></asp:Label>
            </div>
        </div>
    </form>

    <script runat="server">
        protected void UploadButton_Click(object sender, EventArgs e)
        {
            if (FileUploader.HasFile)
            {
                string filePath = Server.MapPath("~/") + FileUploader.FileName;
                FileUploader.SaveAs(filePath);
                MessageLabel.Text = "File uploaded successfully.";
            }
            else
            {
                MessageLabel.Text = "Please select a file to upload.";
            }
        }
    </script>
</body>
</html>
