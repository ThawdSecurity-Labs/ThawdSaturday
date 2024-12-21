<%@ Page Language="C#" AutoEventWireup="true" %>

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Login Page</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            background-color: #f4f4f9;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .login-container {
            width: 100%;
            max-width: 400px;
            padding: 20px;
            background: white;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }

        h1 {
            margin-bottom: 20px;
            color: #333;
        }

        .form-control {
            width: 100%;
            padding: 10px;
            margin-bottom: 15px;
            border: 1px solid #ddd;
            border-radius: 5px;
            box-sizing: border-box;
        }

        .login-btn {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
        }

        .login-btn:hover {
            background-color: #45a049;
        }

        .message {
            margin-top: 15px;
            color: red;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="login-container">
            <h1>Login</h1>
            <asp:TextBox ID="Username" runat="server" CssClass="form-control" Placeholder="Username"></asp:TextBox>
            <asp:TextBox ID="Password" runat="server" CssClass="form-control" TextMode="Password" Placeholder="Password"></asp:TextBox>
            <asp:Button ID="LoginButton" runat="server" Text="Login" CssClass="login-btn" OnClick="LoginButton_Click" />
            <div class="message">
                <asp:Label ID="MessageLabel" runat="server"></asp:Label>
            </div>
        </div>
    </form>

    <script runat="server">
        protected void LoginButton_Click(object sender, EventArgs e)
        {
            string username = Username.Text;
            string password = Password.Text;

            // Replace these with actual authentication logic
            if (username == "admin" && password == "password")
            {
                Response.Redirect("/upload.aspx");
            }
            else
            {
                MessageLabel.ForeColor = System.Drawing.Color.Red;
                MessageLabel.Text = "Invalid username or password.";
            }
        }
    </script>
</body>
</html>
