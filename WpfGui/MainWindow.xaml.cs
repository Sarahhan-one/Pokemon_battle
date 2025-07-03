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
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            game.StartGame();  // C++ StartGame() 호출
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }
    }
}