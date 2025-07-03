using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CppCliWrapper;

namespace Demon_battle
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Wrapper game;
        public MainWindow()
        {
            InitializeComponent();
            game = new Wrapper();

            // Register C# function to be called from C++
            Wrapper.RegisterImageCallback(ShowImages);
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            game.StartGame();  // C++ StartGame() 호출
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }

        public static void ShowImages(List<List<string>> paths)
        {
        var window = (MainWindow)Application.Current.MainWindow;

            var imageControl = window.FindName($"Player_{1}_Image") as Image;
            if (imageControl != null)
            {
                string imagePath = paths[1][0];
                imageControl.Source = new BitmapImage(new Uri(imagePath, UriKind.Relative));
            }

            window.ImageGrid.Children.Clear();
            window.ImageGrid.RowDefinitions.Clear();
            window.ImageGrid.ColumnDefinitions.Clear();

            window.ControlPanel.Visibility = Visibility.Collapsed;
            window.GamePanel.Visibility = Visibility.Visible;

            int rowCount = paths.Count;
            int colCount = paths[0].Count;

            for (int r = 0; r < rowCount; r++)
                window.ImageGrid.RowDefinitions.Add(new RowDefinition());

            for (int c = 0; c < colCount; c++)
                window.ImageGrid.ColumnDefinitions.Add(new ColumnDefinition());

            for (int r = 0; r < rowCount; r++)
            {
                for (int c = 0; c < colCount; c++)
                {
                    string path = paths[r][c];

                    if (string.IsNullOrWhiteSpace(path))
                    {
                        var rect = new Border
                        {
                            Background = Brushes.White,
                            BorderBrush = Brushes.Gray,
                            BorderThickness = new Thickness(1)
                        };
                        Grid.SetRow(rect, r);
                        Grid.SetColumn(rect, c);
                        window.ImageGrid.Children.Add(rect);
                    }
                    else
                    {
                        var image = new Image
                        {
                            Source = new BitmapImage(new Uri(System.IO.Path.GetFullPath(path), UriKind.Absolute)),
                            Stretch = Stretch.Uniform
                        };
                        Grid.SetRow(image, r);
                        Grid.SetColumn(image, c);
                        window.ImageGrid.Children.Add(image);
                    }
                }
            }
        }
    }
}