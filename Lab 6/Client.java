import java.io.*;
import java.net.*;

public class Client
{
    public static void main(String[] args)
    {
        try
        {
            // Connect to the server
            Socket socket = new Socket("localhost", 8080);

            // Get the numbers from the user
            BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
            int num1 = 0, num2 = 0;
            while (true)
            {
                try
                {
                    System.out.print("<Client> Enter the first number: ");
                    num1 = Integer.parseInt(input.readLine());
                    break;
                } catch (NumberFormatException e)
                {
                    System.out.println("<Client> Invalid input.");
                }
            }
            while (true)
            {
                try
                {
                    System.out.print("<Client> Enter the second number: ");
                    num2 = Integer.parseInt(input.readLine());
                    break;
                }
                catch (NumberFormatException e)
                {
                    System.out.println("<Client> Invalid input.");
                }
            }

            // Send the numbers to the server
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);
            writer.println(num1 + " " + num2);

            // Receive the result from the server
            InputStream inputFromServer = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputFromServer));
            String result = reader.readLine();
            System.out.println("<Server> The sum of two numbers: " + result);

            // Close the socket
            socket.close();
        }
        catch (ConnectException e)
        {
            System.out.println("<Client> Failed to connect to the server.");
        }
        catch (IOException e)
        {
            System.out.println("<Client> Error occurred while communicating with the server.");
        }
    }
}