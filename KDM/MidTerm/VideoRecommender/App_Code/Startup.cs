using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(VideoRecommender.Startup))]
namespace VideoRecommender
{
    public partial class Startup {
        public void Configuration(IAppBuilder app) {
            ConfigureAuth(app);
        }
    }
}
