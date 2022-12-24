import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class CircleAreaCalculator extends JFrame {
    JTextField radiusField;
    JLabel resultLabel;

    public CircleAreaCalculator() {
        setTitle("Circle Area Calculator");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        radiusField = new JTextField(10);
        resultLabel = new JLabel("Enter radius and click Calculate");


        JButton calculateButton = new JButton("Calculate");
        calculateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                double radius = Double.parseDouble(radiusField.getText());
                double area = Math.PI * radius * radius;
                resultLabel.setText(String.format("Area of circle: %.2f", area));
            }
        });
        add(radiusField, BorderLayout.NORTH);
        add(resultLabel, BorderLayout.SOUTH);
        add(calculateButton, BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        CircleAreaCalculator form = new CircleAreaCalculator();
        form.setVisible(true);
    }
}
